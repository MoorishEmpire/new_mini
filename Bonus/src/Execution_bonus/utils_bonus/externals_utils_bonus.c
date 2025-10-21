/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:45:39 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:45:40 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

void	command_not_found(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd->argv[0])
		ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	cmd->ctx->exit.exit_status = 127;
}

int	validate_absolute_path(t_cmd *cmd)
{
	if (!cmd->argv[0] || !ft_strchr(cmd->argv[0], '/'))
		return (0);
	if (check_if_directory(cmd->argv[0], cmd))
		return (1);
	if (check_permission(cmd->argv[0], cmd))
		return (1);
	if (check_file_not_exist(cmd))
		return (1);
	return (0);
}

int	is_valid_path(t_cmd *cmd, char *path)
{
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (validate_absolute_path(cmd))
			return (0);
		return (1);
	}
	if (!path || !*path)
	{
		command_not_found(cmd);
		return (0);
	}
	return (1);
}

void	handle_child_exit(int status, t_cmd *cmd)
{
	if (WIFEXITED(status))
		cmd->ctx->exit.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->ctx->exit.exit_status = 128 + WTERMSIG(status);
}

void	cleanup_resources(char *path, char **envp)
{
	if (path)
		free(path);
	if (envp)
		free_split(envp);
}
