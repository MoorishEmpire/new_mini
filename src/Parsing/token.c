/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 16:28:09 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespace(int *i, char *input)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

void	is_it_and(t_token **head, t_token **tail, int *i, char *input)
{
	t_token	*new;

	new = NULL;
	if (input[*i] == '&' && input[*i + 1] == '&')
	{
		new = create_token(AND, "&&", NULL);
		*i += 1;
		(*i)++;
	}
	else
	{
		(*i)++;
		return ;
	}
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

static void	prepare_token_ctx(t_quote_ctx *ctx, int start_index)
{
	ctx->i = start_index;
	ctx->in_q = 0;
	ctx->type = 0;
	ctx->len = 0;
}

void	cr_nd_ap(t_token **h, t_token **tail, char *input, t_quote_ctx *ctx)
{
	t_token	*new;
	int		start;
	int		j;

	new = NULL;
	start = ctx->i - ctx->len;
	if (ctx->len == 0)
		return ;
	j = make_full_token(input, ctx->len, start, &new);
	if (j == -1 || !new)
		return ;
	if (!*h)
		*h = new;
	else
		(*tail)->next = new;
	*tail = new;
}

void	is_it_word(t_token **head, t_token **tail, int *i, char *input)
{
	t_quote_ctx	ctx;

	prepare_token_ctx(&ctx, *i);
	get_full_quote(input, &ctx);
	cr_nd_ap(head, tail, input, &ctx);
	*i = ctx.i;
}
