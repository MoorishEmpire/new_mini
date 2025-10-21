/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:43:08 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 17:04:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_operator(NodeType type)
{
	return (type == PIPE || type == AND || type == OR);
}

static int	check_first_token(t_token *curr, t_ctx *ctx)
{
	if (curr && is_operator(curr->type))
	{
		printf("syntax error near unexpected token `%s'\n", curr->value);
		ctx->exit.exit_status = 258;
		return (1);
	}
	return (0);
}

static int	check_consecutive_ops(t_token *curr, t_ctx *ctx)
{
	if (is_operator(curr->type) && curr->next && is_operator(curr->next->type))
	{
		printf("syntax error near unexpected token `%s'\n", curr->next->value);
		ctx->exit.exit_status = 258;
		return (1);
	}
	return (0);
}

static int	check_last_token(t_token *last, t_ctx *ctx)
{
	if (last && is_operator(last->type))
	{
		printf("syntax error near unexpected token `%s'\n", last->value);
		ctx->exit.exit_status = 258;
		return (1);
	}
	return (0);
}

int	pipe_err(t_token **list, t_ctx *ctx)
{
	t_token	*curr;
	t_token	*last;

	curr = *list;
	last = NULL;
	if (check_first_token(curr, ctx))
		return (1);
	while (curr)
	{
		if (check_consecutive_ops(curr, ctx))
			return (1);
		last = curr;
		curr = curr->next;
	}
	if (check_last_token(last, ctx))
		return (1);
	return (0);
}
