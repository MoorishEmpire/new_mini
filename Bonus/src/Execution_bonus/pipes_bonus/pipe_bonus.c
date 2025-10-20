#include "../../../includes_bonus/minishell_bonus.h"

static int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void	cleanup_pipes(int **pipes, int i)
{
	while (--i >= 0)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
}

static int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe");
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static int	init_pipeline_resources(t_cmd *cmd, int ***pipes, pid_t **pids,
		int count)
{
	*pipes = create_pipes(count - 1);
	if (!(*pipes) && count > 1)
	{
		cmd->ctx->exit.exit_status = 1;
		return (0);
	}
	*pids = malloc(sizeof(pid_t) * count);
	if (!(*pids))
	{
		if (*pipes)
			close_pipes(*pipes, count - 1);
		cmd->ctx->exit.exit_status = 1;
		return (0);
	}
	return (1);
}

void	execute_pipeline(t_cmd *cmd, t_env **env_list, char **env_array)
{
	int			**pipes;
	pid_t		*pids;
	int			cmd_count;
	t_pipeline	ctx;

	cmd_count = count_commands(cmd);
	if (!init_pipeline_resources(cmd, &pipes, &pids, cmd_count))
		return ;
	ctx.pipes = pipes;
	ctx.cmd_count = cmd_count;
	ctx.env_list = env_list;
	ctx.env_array = env_array;
	signal_init_exec();
	fork_and_execute(cmd, pids, &ctx);
	wait_for_children(cmd, pids, cmd_count);
	if (pipes)
		close_pipes(pipes, cmd_count - 1);
	free(pids);
	signal_init_interactive();
}
