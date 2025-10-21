/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:45:18 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 20:45:19 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

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

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
