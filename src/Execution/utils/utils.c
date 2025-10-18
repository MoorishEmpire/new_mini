/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:00:00 by moel-idr          #+#    #+#             */
/*   Updated: 2025/01/20 10:00:00 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return;
		}
		tmp = tmp->next;
	}

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return;
	new_node->var = ft_strdup(var);
	new_node->value = value ? ft_strdup(value) : NULL;
	new_node->next = NULL;
	lstenv_add_back(env, new_node);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*env_to_list(char **env)
{
	t_env	*new_node;
	t_env	*head;
	char	*eq;

	head = NULL;
	while (*env)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		eq = ft_strchr(*env, '=');
		if (eq)
		{
			new_node->var = ft_substr(*env, 0, eq - *env);
			new_node->value = ft_strdup(eq + 1);
		}
		else
		{
			new_node->var = ft_strdup(*env);
			new_node->value = NULL;
		}
		new_node->next = NULL;
		lstenv_add_back(&head, new_node);
		env++;
	}
	return (head);
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
		{
			free_env_list(head);
			return (NULL);
		}
		new_node->var = ft_strdup(env->var);
		new_node->value = env->value ? ft_strdup(env->value) : NULL;
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

void	lstenv_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!*env)
		*env = new_node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key[i] || (!ft_isalpha(key[i]) && key[i] != '_'))
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}



int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	
	return (ft_strcmp(cmd, "echo") == 0 ||
			ft_strcmp(cmd, "cd") == 0 ||
			ft_strcmp(cmd, "pwd") == 0 ||
			ft_strcmp(cmd, "export") == 0 ||
			ft_strcmp(cmd, "unset") == 0 ||
			ft_strcmp(cmd, "env") == 0 ||
			ft_strcmp(cmd, "exit") == 0);
}

