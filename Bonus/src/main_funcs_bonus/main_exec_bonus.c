/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:11:00 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:01:20 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/minishell_bonus.h"

void	execute_cmd(t_cmd *cmd, t_env **env_list)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
	{
		execute_builtin(cmd, env_list);
		return ;
	}
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	exec_builtin_cmd(t_cmd *cmd, t_env **env_list, char **env_array,
		int saved_io[2])
{
	signal_init_exec();
	if (prepare_heredocs(cmd, env_array) == -1 || apply_redirections(cmd,
			env_array) == -1)
	{
		signal_init_interactive();
		perror("redirection");
		return ;
	}
	execute_cmd(cmd, env_list);
	restore_stdio(saved_io[0], saved_io[1]);
	signal_init_interactive();
}

int	handle_redirect_only(t_cmd *cmd, char **env_array)
{
	int	i;
	int	fd;

	if ((!cmd->argv || !cmd->argv[0]) && cmd->redirect && cmd->redirect[0])
	{
		i = 0;
		while (cmd->redirect[i])
		{
			fd = -1;
			if (strcmp(cmd->redirect[i], ">") == 0)
				fd = open(cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (strcmp(cmd->redirect[i], ">>") == 0)
				fd = open(cmd->file[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (strcmp(cmd->redirect[i], "<<") == 0)
				prepare_heredocs(cmd, env_array);
			else if (strcmp(cmd->redirect[i], "<") == 0)
				open(cmd->file[i], O_RDONLY);
			if (fd != -1)
				close(fd);
			i++;
		}
		cmd->ctx->exit.exit_status = 0;
		return (1);
	}
	return (0);
}
