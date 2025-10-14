/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:55 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 18:37:59 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	match_loop(char *pattern, char *str, char **star, char **str_ptr)
{
	while (**str_ptr)
	{
		if (*pattern == '*')
		{
			*star = pattern++;
			str = *str_ptr;
		}
		else if (*pattern == **str_ptr || *pattern == '?')
		{
			pattern++;
			(*str_ptr)++;
		}
		else if (*star)
		{
			pattern = *star + 1;
			str++;
			*str_ptr = str;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

int	match_pattern(char *pattern, char *str)
{
	char	*star;
	char	*str_ptr;
	int		result;

	star = NULL;
	str_ptr = str;
	result = match_loop(pattern, str, &star, &str_ptr);
	return (result);
}

static int	process_directory_entries(DIR *dir, char *token, char **matches)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (should_skip_entry(entry, token))
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(token, entry->d_name))
		{
			if (!add_match_to_array(matches, count, entry->d_name))
				return (cleanup_matches_array(matches, count), -1);
			count++;
		}
		entry = readdir(dir);
	}
	matches[count] = NULL;
	return (count);
}

int	collect_directory_matches(char *token, char **matches)
{
	DIR	*dir;
	int	count;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = process_directory_entries(dir, token, matches);
	closedir(dir);
	return (count);
}
