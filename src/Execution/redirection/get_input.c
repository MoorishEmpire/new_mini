/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:24:51 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 01:24:45 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_out(char *file, int tr_ap, t_cmd *cmd)
{
	int	fd;

	if (tr_ap == 1)
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(file);
		cmd->ctx->exit.exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		cmd->ctx->exit.exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_in(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		cmd->ctx->exit.exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		cmd->ctx->exit.exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
