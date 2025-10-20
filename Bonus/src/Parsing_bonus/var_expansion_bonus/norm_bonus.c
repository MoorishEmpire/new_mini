/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:59:52 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

int	has_unquoted_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space_unquoted(str, i))
			return (1);
		i++;
	}
	return (0);
}

int	handle_token(t_token *xpnd, t_token **result, t_token *prev)
{
	if (xpnd->type == VAR && has_unquoted_space(xpnd->value) && (prev == NULL
			|| prev->type != HERE_DOC))
		return (split_var_token(xpnd, result));
	else
		return (copy_token(xpnd, result));
}

int	token_has_quotes(t_token *token)
{
	char	quote_char;

	quote_char = 0;
	int (i), (in_quotes);
	i = 0;
	in_quotes = 0;
	while (token->value[i])
	{
		if (!in_quotes && (token->value[i] == '\'' || token->value[i] == '"'))
		{
			in_quotes = 1;
			quote_char = token->value[i];
		}
		else if (in_quotes && token->value[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		else if (in_quotes && token->value[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static void	update_quote_state(char c, int *in_quotes, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = c;
		}
		else if (c == *quote_char)
		{
			*in_quotes = 0;
			*quote_char = 0;
		}
	}
}

int	is_space_unquoted(char *str, int index)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (i < index && str[i])
	{
		update_quote_state(str[i], &in_quotes, &quote_char);
		i++;
	}
	if (str[index] == ' ' && !in_quotes)
		return (1);
	return (0);
}
