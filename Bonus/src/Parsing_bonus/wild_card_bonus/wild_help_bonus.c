/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_help_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:55 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:59:52 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

t_token	*make_list(t_token **result, int type, char *value, char *var_nam)
{
	t_token	*new;

	new = create_token(type, value, var_nam);
	if (!new)
	{
		free_token_list(*result);
		*result = NULL;
		return (NULL);
	}
	append_list(result, new);
	return (new);
}

void	cleanup_expansion_results(char **res, int start_index)
{
	while (res[start_index])
		free(res[start_index++]);
	free(res);
}

int	process_regular_token(t_token *token, t_token **result)
{
	return (make_list(result, token->type, token->value,
			token->var_nam) != NULL);
}

int	should_skip_entry(struct dirent *entry, char *token)
{
	if (entry->d_name[0] == '.' && token[0] != '.')
		return (1);
	return (0);
}

int	add_match_to_array(char **matches, int count, char *filename)
{
	matches[count] = ft_strdup(filename);
	if (!matches[count])
		return (0);
	return (1);
}
