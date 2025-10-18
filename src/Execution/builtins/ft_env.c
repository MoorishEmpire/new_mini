#include "../../../includes/minishell.h"

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