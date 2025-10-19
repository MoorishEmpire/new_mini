#include "../../../includes/minishell.h"

static void	delete_env_var(t_env **env, char *var)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->var);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **env, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!args[1])
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", 2);
		return (1);
	}
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			(ft_putstr_fd("minishell: unset: `", 2), ft_putstr_fd(args[i], 2));
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
			delete_env_var(env, args[i]);
		i++;
	}
	cmd->ctx->exit.exit_status = status;
	return (status);
}
