/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:05:52 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 20:34:47 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*strip_str(char *str)
{
	char	*res;
	int		i;
	int		k;
	char	quote;

	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[k++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[k++] = str[i++];
	}
	res[k] = '\0';
	return (res);
}

static void	handle_redirect_quotes(t_token *tok)
{
	if (is_token_redirect(tok) && tok->next)
	{
		if (has_quotes(tok->next->value))
			tok->next->quote_flag = 1;
		else
			tok->next->quote_flag = 0;
	}
}

static char	*get_stripped_value(t_token *tok)
{
	if (tok->type != QUOTED_VAR)
		return (strip_str(tok->value));
	return (ft_strdup(tok->value));
}

static t_token	*create_and_append_token(t_token **result, t_token *xpnd,
		char *res)
{
	t_token	*new;

	new = create_token(xpnd->type, res, xpnd->var_nam);
	if (!new)
	{
		free(res);
		clear_tokens(result);
		return (NULL);
	}
	new->quote_flag = xpnd->quote_flag;
	append_list(result, new);
	return (new);
}

t_token	*stripper(t_token *xpnd)
{
	t_token	*result;
	char	*res;

	result = NULL;
	while (xpnd)
	{
		handle_redirect_quotes(xpnd);
		res = get_stripped_value(xpnd);
		if (!res)
			clear_tokens(&result);
		if (!create_and_append_token(&result, xpnd, res))
			return (NULL);
		free(res);
		xpnd = xpnd->next;
	}
	return (result);
}
