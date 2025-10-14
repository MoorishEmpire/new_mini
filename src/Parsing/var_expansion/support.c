/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 19:05:42 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

int	is_it_var(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	else
		return (0);
}

int	is_it_singled(t_token *token)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (token->type == DOUBLE_QU)
	{
		return (0);
	}
	while (token->value[i])
	{
		if (token->value[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token->value[i] == '"' && !in_single)
			in_double = !in_double;
		else if (token->value[i] == '$' && in_single)
			return (1);
		i++;
	}
	return (0);
}

int	is_it_doubled(t_token *token)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (token->type == SINGL_QU)
	{
		return (0);
	}
	while (token->value[i])
	{
		if (token->value[i] == '"' && !in_single)
			in_double = !in_double;
		else if (token->value[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (token->value[i] == '$' && in_double)
			return (1);
		i++;
	}
	return (0);
}

char	*var_name(char *str)
{
	char	*dollar;
	char	*tmp;

	int (i), (j), (start);
	j = 0;
	tmp = ft_strchr(str, '$');
	if (!tmp)
		return (NULL);
	start = 1;
	i = 0;
	while (tmp[start + i] && (ft_isalnum(tmp[start + i])
			|| tmp[start + i] == '_'))
		i++;
	dollar = malloc(sizeof(char) * (i + 1));
	if (!dollar)
		return (NULL);
	while (j < i)
	{
		dollar[j] = tmp[start + j];
		j++;
	}
	dollar[i] = '\0';
	return (dollar);
}
