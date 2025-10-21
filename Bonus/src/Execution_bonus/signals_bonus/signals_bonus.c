/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:30:36 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:30:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

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
