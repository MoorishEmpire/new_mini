/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:45:46 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:45:48 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
