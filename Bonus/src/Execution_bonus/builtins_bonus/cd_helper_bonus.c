#include "../../../includes_bonus/minishell_bonus.h"

char	*cd_home_error(char *oldpwd, t_cmd *cmd)
{
	free(oldpwd);
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	cmd->ctx->exit.exit_status = 1;
	return (NULL);
}

char	*cd_oldpwd_error(char *oldpwd, t_cmd *cmd)
{
	free(oldpwd);
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	cmd->ctx->exit.exit_status = 1;
	return (NULL);
}

char	*expand_tilde(char *path, t_env **env)
{
	char	*home;
	char	*expanded;

	if (!path || path[0] != '~')
		return (path);
	home = get_env(*env, "HOME");
	if (!home)
		return (path);
	if (path[1] == '\0')
		return (ft_strdup(home));
	if (path[1] == '/')
	{
		expanded = ft_strjoin(home, path + 1);
		return (expanded);
	}
	return (path);
}
