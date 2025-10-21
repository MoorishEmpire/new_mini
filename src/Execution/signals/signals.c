/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:42:17 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:42:18 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_signal_received(void)
{
	return (g_signal_received != 0);
}

void	reset_signal_received(void)
{
	g_signal_received = 0;
}

void	signal_check(t_cmd *cmd)
{
	if (g_signal_received == SIGINT)
	{
		g_signal_received = 0;
		cmd->ctx->exit.exit_status = 130;
	}
	else if (g_signal_received == SIGTERM)
	{
		g_signal_received = 0;
		cmd->ctx->exit.exit_status = 143;
	}
}
