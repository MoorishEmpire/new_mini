/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:13:58 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:55:37 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

static int	handle_redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->redirect[i])
	{
		if (strcmp(cmd->redirect[i], ">>") == 0)
			if (handle_out(cmd->file[i], 1, cmd) == -1)
				return (-1);
		if (strcmp(cmd->redirect[i], ">") == 0)
			if (handle_out(cmd->file[i], 0, cmd) == -1)
				return (-1);
		if (strcmp(cmd->redirect[i], "<") == 0)
			if (handle_in(cmd->file[i], cmd) == -1)
				return (-1);
		i++;
	}
	return (0);
}

int prepare_heredocs(t_cmd *cmd, char **env)
{
    int fd;
    int i;

    fd = -1;
    i = 0;
    while (cmd->redirect && cmd->redirect[i])
    {
        if (ft_strncmp(cmd->redirect[i], "<<", 2) == 0)
        {
            int new_fd = handle_heredoc(cmd->file[i], env, cmd, i);
            if (new_fd == -1)
                return (-1);
            if (fd != -1)
                close(fd);
            fd = new_fd;
        }
        i++;
    }
    cmd->here_fd = fd;
    return (0);
}

int	apply_redirections(t_cmd *cmd, char **env)
{
	(void)env;
	if (handle_redirections(cmd) == -1)
		return (-1);
	if (cmd->here_fd != -1)
	{
		dup2(cmd->here_fd, STDIN_FILENO);
		close(cmd->here_fd);
	}
	return (0);
}

