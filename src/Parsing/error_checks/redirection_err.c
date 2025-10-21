/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:43:08 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 16:42:37 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	redir_check(t_token *token, t_ctx *ctx)
{
	if (!token)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		ctx->exit.exit_status = 258;
		return (1);
	}
	if (is_token_redirect(token) || is_it_opp(token))
	{
		printf("syntax error near unexpected token `%s'\n", token->value);
		ctx->exit.exit_status = 258;
		return (1);
	}
	if ((token->type == VAR || token->type == QUOTED_VAR)
		&& is_empty_string(token))
	{
		printf("bash: : ambiguous redirect\n");
		ctx->exit.exit_status = 258;
		return (1);
	}
	if ((token->type == VAR || token->type == QUOTED_VAR)
		&& (ft_isspace(token->value) || (token->var_nam != NULL && token->next
				&& token->var_nam == token->next->var_nam)))
	{
		printf("bash: : ambiguous redirect\n");
		ctx->exit.exit_status = 258;
		return (1);
	}
	return (0);
}
