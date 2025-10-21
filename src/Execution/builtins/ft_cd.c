
#include "../../../includes/minishell.h"

static char	*get_cd_path(char **args, t_env **env, char *oldpwd, t_cmd *cmd)
{
	char	*path;

	if (!args[1])
	{
		path = get_env(*env, "HOME");
		if (!path)
			return (cd_home_error(oldpwd, cmd));
		return (ft_strdup(path));
	}
	if (!ft_strcmp(args[1], "-"))
	{
		path = get_env(*env, "OLDPWD");
		if (!path)
			return (cd_oldpwd_error(oldpwd, cmd));
		return (ft_strdup(path));
	}
	return (expand_tilde(args[1], env));
}

static int	cd_error(char *path, char *oldpwd, int is_path_allocated,
	t_cmd *cmd)
{
free(oldpwd);
ft_putstr_fd("minishell: cd: ", 2);
ft_putstr_fd(path, 2);

if (errno == ENOENT)
	ft_putstr_fd(": No such file or directory\n", 2);
else if (errno == ENOTDIR)
	ft_putstr_fd(": Not a directory\n", 2);
else if (errno == EACCES)
	ft_putstr_fd(": Permission denied\n", 2);
else if (errno == ELOOP)
	ft_putstr_fd(": Too many symbolic links encountered\n", 2);
else if (errno == ENAMETOOLONG)
	ft_putstr_fd(": File name too long\n", 2);
else if (errno == ENFILE)
	ft_putstr_fd(": File table overflow\n", 2);

if (is_path_allocated)
	free(path);
cmd->ctx->exit.exit_status = 1;
return (1);
}

static void	update_cd_env(t_env **env, char *oldpwd, char *newpwd,
		int print_newpwd)
{
	update_env_var(env, "OLDPWD", oldpwd);
	update_env_var(env, "PWD", newpwd);
	if (print_newpwd && newpwd)
		printf("%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
}

int	ft_cd(char **args, t_env **env, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;
	int		is_path_allocated;
	int		print_newpwd;

	is_path_allocated = 0;
	oldpwd = getcwd(NULL, 0);
	print_newpwd = (args[1] && !ft_strcmp(args[1], "-"));
	path = get_cd_path(args, env, oldpwd, cmd);
	if (!path)
		return (1);
	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "-"))
		is_path_allocated = 1;
	if (chdir(path) == -1)
		return (cd_error(path, oldpwd, is_path_allocated, cmd));
	newpwd = getcwd(NULL, 0);
	update_cd_env(env, oldpwd, newpwd, print_newpwd);
	if (is_path_allocated)
		free(path);
	cmd->ctx->exit.exit_status = 0;
	return (0);
}
