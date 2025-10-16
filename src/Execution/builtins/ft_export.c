#include "../../../includes/minishell.h"


static void print_export(t_env *env)
{
    t_env   *sorted_env;
    t_env   *tmp;

    sorted_env = copy_env_list(env);
    if (!sorted_env)
        return;
    sort_env_list(&sorted_env);
    tmp = sorted_env;
    while (tmp)
    {
        printf("declare -x %s", tmp->var);
        if (tmp->value)
            printf("=\"%s\"", tmp->value);
        printf("\n");
        tmp = tmp->next;
    }
    free_env_list(sorted_env);
}

int	is_valid_key(char *key)
{
    int i;
    
    if (!key || !key[0])
        return (0);
    i = 0;
    if (!ft_isalpha(key[i]) && key[i] != '_')
        return (0);
    
    i++;
    while (key[i] && key[i] != '=')
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int process_export_arg(char *arg, t_env **env)
{
    char *var;
    char *value;
    char *equal_sign;

    if (!is_valid_key(arg))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (1);
    }

    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        var = ft_substr(arg, 0, equal_sign - arg);
        value = ft_strdup(equal_sign + 1);
        update_env_var(env, var, value);
        free(var);
        free(value);
    }
    else
        update_env_var(env, arg, NULL);
    return (0);
}

int ft_export(char **args, t_env **env, t_cmd *cmd)
{
    int i;
    int status;

    if (!args[1])
    {
        print_export(*env);
        return (0);
    }
    i = 1;
    status = 0;
    while (args[i])
    {
		if(args[i][0] == '\0')
			printf("bash: export: `': not a valid identifier\n");
        if (process_export_arg(args[i], env))
            status = 1;
        i++;
    }
    cmd->exit_status = status;
    return (status);
}