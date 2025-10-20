#include "../../../includes_bonus/minishell_bonus.h"

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

int	has_input_redirection(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirect && cmd->redirect[i])
	{
		if (strcmp(cmd->redirect[i], "<") == 0 || strcmp(cmd->redirect[i],
				"<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	setup_pipes(int idx, t_pipeline *ctx, int has_out_redir,
		int has_in_redir)
{
	int i;

	if (idx > 0 && !has_in_redir)
		dup2(ctx->pipes[idx - 1][0], STDIN_FILENO);
	if (idx < ctx->cmd_count - 1 && !has_out_redir)
		dup2(ctx->pipes[idx][1], STDOUT_FILENO);
	i = 0;
	while (i < ctx->cmd_count - 1)
	{
		close(ctx->pipes[i][0]);
		close(ctx->pipes[i][1]);
		i++;
	}
}

void	execute_pipe_child(t_cmd *cmd, int idx, t_pipeline *ctx)
{
	int	has_in_redir;
	int	has_out_redir;

	signal_init_child();
	if (apply_redirections(cmd, ctx->env_array) == -1)
		exit(1);
	has_in_redir = has_input_redirection(cmd);
	has_out_redir = has_output_redirection(cmd);
	setup_pipes(idx, ctx, has_out_redir, has_in_redir);
	if (is_builtin(cmd->argv[0]))
		exec_builtin_in_pipe(cmd, ctx->env_list);
	else
		exec_external_in_pipe(cmd, ctx->env_array, *ctx->env_list);
}
