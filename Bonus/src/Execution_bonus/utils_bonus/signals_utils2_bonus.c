#include "../../../includes_bonus/minishell_bonus.h"

void	handel_fork_error(t_cmd *cmd)
{
	perror("fork");
	cmd->ctx->exit.exit_status = 1;
}

char	*get_command_path(t_cmd *cmd, t_env *env_list)
{
	char	*path;

	path = NULL;
	if (!ft_strchr(cmd->argv[0], '/'))
		path = get_cmd_path(cmd->argv[0], env_list);
	return (path);
}

int	check_if_directory(const char *path, t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		cmd->ctx->exit.exit_status = 126;
		return (1);
	}
	return (0);
}

int	check_permission(const char *path, t_cmd *cmd)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		cmd->ctx->exit.exit_status = 126;
		return (1);
	}
	return (0);
}

int	check_file_not_exist(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->ctx->exit.exit_status = 127;
		return (1);
	}
	return (0);
}
