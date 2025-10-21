/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:31:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:02:45 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/minishell_bonus.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("\n\nToken is: %s\n", tokens->value);
		tokens = tokens->next;
	}
}

void	init_context(t_ctx *ctx)
{
	ctx->exit.exit_status = 0;
	signal_init_interactive();
}

void	print_parse(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf(RED "(commands) argv[%d]: %s\n" RESET, i, cmd->argv[i]);
			i++;
		}
		if (cmd->redirect && cmd->file)
		{
			i = 0;
			while (cmd->redirect[i] && cmd->file[i])
			{
				printf(YELLOW "Redirect[%d]: %s\n" RESET, i, cmd->redirect[i]);
				printf(SKYBLUE "File[%d]: %s\n" RESET, i, cmd->file[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}
