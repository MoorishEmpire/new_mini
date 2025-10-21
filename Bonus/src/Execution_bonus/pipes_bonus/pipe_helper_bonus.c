/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:08:12 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:26:21 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

void	wait_for_children(t_cmd *cmd, pid_t *pids, int cmd_count)
{
	int	status;
	int	i;
	int	signal;

	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			break ;
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				cmd->ctx->exit.exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				signal = WTERMSIG(status);
				cmd->ctx->exit.exit_status = 128 + WTERMSIG(status);
				if (signal == SIGQUIT)
					ft_putstr_fd("Quit: 3\n", 2);
				else if (signal == SIGINT)
					ft_putstr_fd("\n", 2);
			}
		}
		i++;
	}
}

void	fork_and_execute(t_cmd *cmd, pid_t *pids, t_pipeline *ctx)
{
	int		i;
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		prepare_heredocs(current, ctx->env_array);
		current = current->next;
	}
	current = cmd;
	i = -1;
	while (current && i++ < ctx->cmd_count)
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
	}
}
