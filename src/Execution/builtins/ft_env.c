#include "../../../includes/minishell.h"

void free_env_list(t_env *env)
{
    t_env   *tmp;

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

void    lstenv_add_back(t_env **env, t_env *new_node)
{
    t_env   *tmp;

    if (!env || !new_node)
        return;

    if (!*env)
    {
        *env = new_node;
        return;

    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;

}

static void swap_env_nodes(t_env *node1, t_env *node2)
{
    char *temp_var;
    char *temp_value;

    temp_var = node1->var;
    node1->var = node2->var;
    node2->var = temp_var;

    temp_value = node1->value;
    node1->value = node2->value;
    node2->value = temp_value;
}

/*
void sort_env_list(t_env **env)
{
    t_env   *i;
    t_env   *j;

    i = *env;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strcmp(i->var, j->var) > 0)
            {
                swap_env_nodes(i, j);
            }
            j = j->next;
        }
        i = i->next;
    }
}

*/

void sort_env_list(t_env **env)
{
    t_env   *i;
    t_env   *j;

    if (!env || !*env)  // Add this check
        return;
    
    i = *env;
    while (i && i->next)  // Add bounds check here
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
/*
static  t_env   *new_env_node(char *var, char *value)
{
    t_env   *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->var = ft_strdup(var);
    if (!new_node->var)
    {
        free(new_node);
        return (NULL);
    }
    new_node->value = value ? ft_strdup(value) : NULL;
    if (!new_node->value)
    {
        free(new_node->var);
        free(new_node);
        return (NULL);
    }
    new_node->next = NULL;
    return (new_node);
}
    */

t_env   *copy_env_list(t_env *env)
{
    t_env   *new_node;
    t_env   *head;
    t_env   *last;

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

t_env   *env_to_list(char **env)
{
    t_env   *new_node;
    t_env   *head;
    char    *eq;

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

char    **list_to_env(t_env *list)
{
    char    **env;
    t_env   *tmp;
    char    *entry;
    int     count;
    int     i;

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

void    update_env_var(t_env **env, char *var, char *value)
{
    t_env   *tmp;
    t_env   *new_node;

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
    new_node->var = ft_strdup(var);
    new_node->value = value ? ft_strdup(value) : NULL;
    new_node->next = NULL;
    lstenv_add_back(env, new_node);
}

int	ft_env(t_env *env)
{
    while (env)
    {
        if (env->value && env->var)
            printf("%s=%s\n", env->var, env->value);
        env = env->next;
    }
    return (0);
}