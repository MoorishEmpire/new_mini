/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:30:28 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:30:29 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

void	signal_handler_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_received = SIGINT;
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_received = SIGINT;
		rl_catch_signals = 0;
		if (close(STDIN_FILENO) == -1)
			perror("close");
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return ;
		exit(130);
	}
}

void	signal_reinit_after_fork(int context)
{
	if (context == SIGNAL_INTERACTIVE)
		signal_init_interactive();
	else if (context == SIGNAL_EXEC)
		signal_init_exec();
	else if (context == SIGNAL_HEREDOC)
		signal_init_heredoc();
	else if (context == SIGNAL_CHILD)
		signal_init_child();
}

void	signal_restore_default(void)
{
	signal_init_child();
}
