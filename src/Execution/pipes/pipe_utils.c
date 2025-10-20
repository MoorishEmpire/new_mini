#include "../../../includes/minishell.h"

void	exec_external_in_pipe(t_cmd *cmd, char **envp, t_env *env_list)
{
	char	*path;

	path = get_cmd_path(cmd->argv[0], env_list);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror("minishell: execve");
	free(path);
	exit(126);
}

int	has_output_redirection(t_cmd *cmd)
{
	int	i;

	if (!cmd->redirect)
		return (0);
	i = 0;
	while (cmd->redirect[i])
	{
		if (strcmp(cmd->redirect[i], ">") == 0 || strcmp(cmd->redirect[i],
				">>") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	execute_pipe_child(t_cmd *cmd, int idx, t_pipeline *ctx)
{
	int	has_out_redir;

	signal_init_child();
	has_out_redir = has_output_redirection(cmd);
	if (apply_redirections(cmd, ctx->env_array) == -1)
		exit(1);
	setup_pipe_redirections(ctx->pipes, idx, ctx->cmd_count, has_out_redir);
	if (is_builtin(cmd->argv[0]))
		exec_builtin_in_pipe(cmd, ctx->env_list);
	else
		exec_external_in_pipe(cmd, ctx->env_array, *ctx->env_list);
}

void	wait_for_children(t_cmd *cmd, pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("minishell: waitpid");
			i++;
			continue ;
		}
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				cmd->ctx->exit.exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cmd->ctx->exit.exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	fork_and_execute(t_cmd *cmd, pid_t *pids, t_pipeline *ctx)
{
	int		i;
	t_cmd	*current;

	current = cmd;
	i = 0;
	while (current && i < ctx->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("minishell: fork");
			cmd->ctx->exit.exit_status = 1;
			break ;
		}
		else if (pids[i] == 0)
			execute_pipe_child(current, i, ctx);
		close_parent_pipes(ctx->pipes, i, ctx->cmd_count);
		current = current->next;
		i++;
	}
}
