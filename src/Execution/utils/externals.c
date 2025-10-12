#include "../../../includes/minishell.h"

void    handel_fork_error(void)
{
    perror("fork");
    g_exit_status = 1;
}


int is_valid_path(t_cmd *cmd, char **path)
{
    if (!*path)
    {
        path_not_found(cmd);
        return (0);
    }
    return (1);
}

void	path_not_found(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": Permission denied", 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 126;
		return ;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 127;
	}
}

void    execute_child_process(t_cmd *cmd, char *path, char **envp)
{
    if (path)
        execve(path, cmd->argv, envp);

    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found", 2);
    ft_putstr_fd("\n", 2);

    if (path)
        free(path);
    if (envp)
        free_split(envp);
    g_exit_status = 127;
    exit(127);
}

void execute_externals(t_cmd *cmd, t_env **env_list)
{
    pid_t   pid;
    char    *path;
    int     status;
    char    **envp;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;

    path = get_cmd_path(cmd->argv[0]);
    if (!is_valid_path(cmd, &path) == 0)
        return;

    envp = list_to_env(env);
    if (!envp)
    {
        if (path)
            free(path);
        return;
    }*

    pid = fork();
    if (pid == 0)
        execute_child_process(cmd, path, envp);
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        //signaling to do
        free(path);
        free_split(envp);
    }
    else
        handel_fork_error();
}