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
