/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:55 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:59:57 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

int	no_matches(char *token)
{
	DIR				*dir;
	int				count;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && token[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(token, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

int	matched_count(char *token)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && token[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(token, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char	**expand_wildcard(char *token, t_nodetype type)
{
	char	**matches;
	int		total;
	int		result_count;

	total = matched_count(token);
	matches = init_matches_array(total);
	if (!matches)
		return (NULL);
	if (no_matches(token) == 0 || type == QUOTED_VAR)
		return (handle_no_expansion_case(token));
	result_count = collect_directory_matches(token, matches);
	if (result_count == -1)
	{
		free(matches);
		return (NULL);
	}
	return (matches);
}

int	process_wildcard_token(t_token *token, t_token **result)
{
	char	**res;
	int		i;

	res = expand_wildcard(token->value, token->type);
	if (!res)
		return (0);
	i = 0;
	while (res[i])
	{
		if (!make_list(result, token->type, res[i], token->var_nam))
		{
			cleanup_expansion_results(res, i);
			return (0);
		}
		free(res[i]);
		i++;
	}
	free(res);
	return (1);
}

t_token	*handel_wild_card(t_token *xpnd)
{
	t_token	*result;

	result = NULL;
	while (xpnd)
	{
		if (ft_strchr(xpnd->value, '*'))
		{
			if (!process_wildcard_token(xpnd, &result))
				return (NULL);
		}
		else
		{
			if (!process_regular_token(xpnd, &result))
				return (NULL);
		}
		xpnd = xpnd->next;
	}
	return (result);
}
