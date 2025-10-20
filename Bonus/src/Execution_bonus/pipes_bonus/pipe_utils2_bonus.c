#include "../../../includes_bonus/minishell_bonus.h"

void	exec_builtin_in_pipe(t_cmd *cmd, t_env **env_list)
{
	execute_cmd(cmd, env_list);
	exit(cmd->ctx->exit.exit_status);
}

void	close_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			pipes[i] = NULL;
		}
		i++;
	}
	free(pipes);
}

void	setup_pipe_redirections(int **pipes, int idx, int total,
		int has_output_redir)
{
	int	i;

	if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < total - 1 && !has_output_redir)
		dup2(pipes[idx][1], STDOUT_FILENO);
	i = 0;
	while (i < total - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	close_parent_pipes(int **pipes, int idx, int total)
{
	if (idx > 0)
		close(pipes[idx - 1][0]);
	if (idx < total - 1)
		close(pipes[idx][1]);
}
