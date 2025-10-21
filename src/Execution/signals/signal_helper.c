/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:41:56 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:41:58 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	setup_sigaction(int sig, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		return ;
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	if (sigaction(sig, &sa, NULL) == -1)
		perror("sigaction");
}

void	signal_init_interactive(void)
{
	setup_sigaction(SIGINT, signal_handler_interactive, SA_RESTART);
	setup_sigaction(SIGQUIT, SIG_IGN, SA_RESTART);
	setup_sigaction(SIGPIPE, SIG_IGN, SA_RESTART);
	rl_catch_signals = 0;
}

void	signal_init_exec(void)
{
	setup_sigaction(SIGINT, SIG_IGN, 0);
	setup_sigaction(SIGQUIT, SIG_IGN, 0);
	setup_sigaction(SIGPIPE, SIG_IGN, 0);
}

void	signal_init_heredoc(void)
{
	setup_sigaction(SIGINT, signal_handler_heredoc, 0);
	setup_sigaction(SIGQUIT, SIG_IGN, 0);
	setup_sigaction(SIGPIPE, SIG_IGN, 0);
	rl_catch_signals = 0;
}

void	signal_init_child(void)
{
	setup_sigaction(SIGINT, SIG_DFL, 0);
	setup_sigaction(SIGQUIT, SIG_DFL, 0);
	setup_sigaction(SIGPIPE, SIG_DFL, 0);
}
