#include "../../../includes/minishell.h"


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