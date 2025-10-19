/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:13:58 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/19 21:16:20 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_heredocs(t_cmd *cmd, char **env, int *last_fd)
{
	int	i;

	i = 0;
	while (cmd->redirect[i])
	{
		if (ft_strncmp(cmd->redirect[i], "<<", 2) == 0)
		{
			if (*last_fd != -1)
				close(*last_fd);
			*last_fd = handle_heredoc(cmd->file[i], env, cmd, i);
			if (*last_fd == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

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

int	apply_redirections(t_cmd *cmd, char **env)
{
	int	last_heredoc_fd;

	last_heredoc_fd = -1;
	if (handle_heredocs(cmd, env, &last_heredoc_fd) == -1)
	{
		if (last_heredoc_fd != -1)
			close(last_heredoc_fd);
		return (-1);
	}
	if (handle_redirections(cmd) == -1)
	{
		if (last_heredoc_fd != -1)
			close(last_heredoc_fd);
		return (-1);
	}
	if (last_heredoc_fd != -1)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) == -1)
		{
			close(last_heredoc_fd);
			return (perror("minishell: dup2"), -1);
		}
		close(last_heredoc_fd);
	}
	return (0);
}
