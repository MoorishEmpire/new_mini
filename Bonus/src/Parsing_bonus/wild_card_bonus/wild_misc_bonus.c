/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_misc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:55 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:59:52 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

char	**init_matches_array(int total_count)
{
	char	**matches;

	matches = malloc((total_count + 1) * sizeof(char *));
	return (matches);
}

char	**handle_no_expansion_case(char *token)
{
	char	**matches;

	matches = ft_split(token, '\0');
	return (matches);
}

void	cleanup_matches_array(char **matches, int count)
{
	while (count-- > 0)
		free(matches[count]);
	free(matches);
}
