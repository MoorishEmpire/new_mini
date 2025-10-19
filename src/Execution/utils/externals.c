#include "../../../includes/minishell.h"

static void    handel_fork_error(t_cmd *cmd)
{
    perror("fork");
    cmd->ctx->exit.exit_status = 1;
}

static void path_not_found(t_cmd *cmd)
{
    if (cmd->argv[0] && ft_strchr(cmd->argv[0], '/'))
    {
        if (access(cmd->argv[0], F_OK) == 0)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            cmd->ctx->exit.exit_status = 126;
            return;
        }
    }

    ft_putstr_fd("minishell: ", 2);
    if (cmd->argv[0])
        ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    cmd->ctx->exit.exit_status = 127;
}

static int is_valid_path(t_cmd *cmd, char *path)
{
    if (!path || !*path)
    {
        path_not_found(cmd);
        return 0;
    }
    return 1;
}

static void    execute_child_process(t_cmd *cmd, char *path, char **envp)
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
    cmd->ctx->exit.exit_status = 127;
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

    if (ft_strcmp(cmd->argv[0], "!") == 0 || ft_strcmp(cmd->argv[0], ":") == 0)
    {
        signal_init_interactive();
        return;
    }

    path = get_cmd_path(cmd->argv[0], *env_list);
    if (!is_valid_path(cmd, path))
        return;

    envp = list_to_env(*env_list);
    if (!envp)
    {
        if (path)
            free(path);
        return;
    }

    signal_init_exec();
    pid = fork();
    if (pid == 0)
    {
        signal_init_child();
        if (apply_redirections(cmd, envp) == -1)
		{
			perror("redirection");
			exit(1);
		}
        execute_child_process(cmd, path, envp);

    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        //signaling to do
       cmd->ctx->exit.exit_status = WEXITSTATUS(status);
        free(path);
        free_split(envp);
    }
    else
        handel_fork_error(cmd);
    signal_init_interactive();
}
