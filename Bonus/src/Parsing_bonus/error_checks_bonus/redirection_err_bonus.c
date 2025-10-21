/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_err_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:43:08 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:06:14 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	print_redir_error(t_ctx *ctx, char *msg)
{
	printf("%s", msg);
	ctx->exit.exit_status = 258;
	return (1);
}

int	is_ambiguous_redirect(t_token *token)
{
	if ((token->type == VAR || token->type == QUOTED_VAR)
		&& (is_empty_string(token)
			|| ft_isspace(token->value)
			|| (token->var_nam && token->next
				&& token->var_nam == token->next->var_nam)))
		return (1);
	return (0);
}

int	redir_check(t_token *token, t_ctx *ctx)
{
	if (!token)
		return (print_redir_error(ctx,
				"bash: syntax error near unexpected token `newline'\n"));
	if (is_token_redirect(token) || is_it_opp(token))
	{
		printf("syntax error near unexpected token `%s'\n", token->value);
		ctx->exit.exit_status = 258;
		return (1);
	}
	if (is_ambiguous_redirect(token))
		return (print_redir_error(ctx, "bash: : ambiguous redirect\n"));
	return (0);
}
