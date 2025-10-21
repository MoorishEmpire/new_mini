/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:43:50 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:43:52 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_env(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	increment_shlvl(t_env **env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env(*env, "SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
		shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level ", 2);
		ft_putstr_fd("(1000) too high, resetting to 1\n", 2);
		shlvl = 0;
	}
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	update_env_var(env, "SHLVL", new_shlvl);
	free(new_shlvl);
	if (shlvl_str)
		free(shlvl_str);
}

void	lstenv_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static void	swap_env_nodes(t_env *node1, t_env *node2)
{
	char	*temp_var;
	char	*temp_value;

	temp_var = node1->var;
	node1->var = node2->var;
	node2->var = temp_var;
	temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
}

void	sort_env_list(t_env **env)
{
	t_env	*i;
	t_env	*j;

	if (!env || !*env)
		return ;
	i = *env;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			if (i->var && j->var && ft_strcmp(i->var, j->var) > 0)
			{
				swap_env_nodes(i, j);
			}
			j = j->next;
		}
		i = i->next;
	}
}
