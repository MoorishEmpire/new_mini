/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:05:52 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 18:54:54 by moel-idr         ###   ########.fr       */
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

t_token *stripper(t_token *xpnd)
{
    t_token *result = NULL;
    t_token *new;
    char *res;

    while (xpnd)
    {
        if (is_token_redirect(xpnd) && xpnd->next)
        {
            if (has_quotes(xpnd->next->value))
                xpnd->next->quote_flag = 1;
            else
                xpnd->next->quote_flag = 0;
        }
        if (xpnd->type != QUOTED_VAR)
            res = strip_str(xpnd->value);
        else
            res = ft_strdup(xpnd->value);

        if (!res)
            clear_tokens(&result);

        new = create_token(xpnd->type, res, xpnd->var_nam);
        new->quote_flag = xpnd->quote_flag;
        if (!new)
        {
            free(res);
            clear_tokens(&result);
        }
        append_list(&result, new);
        free(res);
        xpnd = xpnd->next;
    }
    return result;
}
