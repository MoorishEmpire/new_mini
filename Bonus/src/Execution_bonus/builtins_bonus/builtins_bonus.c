/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:03 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 20:22:36 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

static void	run_builtin(t_cmd *cmd, t_env **env)
{
	char	*name;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	name = cmd->argv[0];
	if (ft_strcmp(name, "echo") == 0)
		ft_echo(cmd->argv, cmd);
	else if (ft_strcmp(name, "cd") == 0)
		cmd->ctx->exit.exit_status = ft_cd(cmd->argv, env, cmd);
	else if (ft_strcmp(name, "pwd") == 0)
		cmd->ctx->exit.exit_status = ft_pwd();
	else if (ft_strcmp(name, "env") == 0)
		cmd->ctx->exit.exit_status = ft_env(*env);
	else if (ft_strcmp(name, "exit") == 0)
		ft_exit(cmd->argv, cmd);
	else if (ft_strcmp(name, "export") == 0)
		cmd->ctx->exit.exit_status = ft_export(cmd->argv, env, cmd);
	else if (ft_strcmp(name, "unset") == 0)
		cmd->ctx->exit.exit_status = ft_unset(cmd->argv, env, cmd);
	else
	{
		(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(name, 2));
		ft_putstr_fd(": command not found\n", 2);
		cmd->ctx->exit.exit_status = CMD_NOT_FOUND;
	}
}

int	execute_builtin(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	run_builtin(cmd, env);
	return (cmd->ctx->exit.exit_status);
}
