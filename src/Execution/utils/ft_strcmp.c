/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:43:39 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:43:40 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	env_count(t_env *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->var)
			count++;
		list = list->next;
	}
	return (count);
}

char	*make_env_entry(t_env *node)
{
	char	*entry;
	char	*result;

	entry = ft_strjoin(node->var, "=");
	if (node->value)
		result = ft_strjoin(entry, node->value);
	else
		result = ft_strjoin(entry, "");
	free(entry);
	return (result);
}

char	**list_to_env(t_env *list)
{
	char	**env;
	int		count;
	int		i;

	count = env_count(list);
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (list)
	{
		if (list->var)
			env[i++] = make_env_entry(list);
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
