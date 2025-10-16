#include "../../../includes/minishell.h"

static char	*get_env(t_env *env, char *var)
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

static char	*cd_home_error(char *oldpwd, t_cmd *cmd)
{
	free(oldpwd);
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	cmd->ctx->exit.exit_status = 1;
	return (NULL);
}

static char	*cd_oldpwd_error(char *oldpwd, t_cmd *cmd)
{
	free(oldpwd);
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	cmd->ctx->exit.exit_status = 1;
	return (NULL);
}

static char	*get_cd_path(char **args, t_env **env, char *oldpwd, t_cmd *cmd)
{
	char	*path;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env(*env, "HOME");
		if (!path)
			return (cd_home_error(oldpwd, cmd));
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = get_env(*env, "OLDPWD");
		if (!path)
			return (cd_oldpwd_error(oldpwd, cmd));
	}
	else
		path = args[1];
	return (path);
}

int			ft_cd(char **args, t_env **env, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		print_newpwd;
	int		is_path_allocated;

	is_path_allocated = 0;
	oldpwd = getcwd(NULL, 0);
	print_newpwd = (args[1] && !ft_strcmp(args[1], "-"));
	path = get_cd_path(args, env, oldpwd, cmd);
	if (!path)
		return (1);

	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "-"))
		is_path_allocated = 1;
	
	if (chdir(path) == -1)
	{
		free(oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);	cmd = NULL;
		ft_putstr_fd(": No such file or directory\n", 2);
		if (is_path_allocated)
			free(path);
		cmd->ctx->exit.exit_status = 1;
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	if (print_newpwd && newpwd)
		printf("%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
	if (is_path_allocated)
		free(path);
	cmd->ctx->exit.exit_status = 0;
	return (0);
}
