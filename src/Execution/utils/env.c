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

char	**list_to_env(t_env *list)
{
	char	**env;
	t_env	*tmp;
	char	*entry;
	int		count;
	int		i;

	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->var)
			count++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (list)
	{
		if (list->var)
		{
			entry = ft_strjoin(list->var, "=");
			env[i++] = ft_strjoin(entry, list->value ? list->value : "");
			free(entry);
		}
		list = list->next;
	}
	env[count] = NULL;
	return (env);
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
	new_node->value = value ? ft_strdup(value) : NULL;
	new_node->next = NULL;
	lstenv_add_back(env, new_node);
}
