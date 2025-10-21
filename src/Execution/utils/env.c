/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:42:43 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:42:45 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = tmp->next;
		free(env->var);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*new_node;
	t_env	*head;
	t_env	*last;

	head = NULL;
	last = NULL;
	while (env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (free_env_list(head), NULL);
		new_node->var = ft_strdup(env->var);
		if (env->value)
			new_node->value = ft_strdup(env->value);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			last->next = new_node;
		last = new_node;
		env = env->next;
	}
	return (head);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = ft_strchr(env_str, '=');
	if (eq)
	{
		node->var = ft_substr(env_str, 0, eq - env_str);
		node->value = ft_strdup(eq + 1);
	}
	else
	{
		node->var = ft_strdup(env_str);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

t_env	*env_to_list(char **env)
{
	t_env	*head;
	t_env	*new_node;

	head = NULL;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!new_node)
			return (NULL);
		lstenv_add_back(&head, new_node);
		env++;
	}
	return (head);
}

void	update_env_var(t_env **env, char *var, char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var) == 0)
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->var = ft_strdup(var);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	lstenv_add_back(env, new_node);
}
