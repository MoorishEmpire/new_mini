#include "../../../includes/minishell.h"

void    exec_builtin_in_pipe(t_cmd *cmd, t_env **env_list)
{
    execute_cmd(cmd, env_list);
    exit(cmd->ctx->exit.exit_status);
}

void    exec_external_in_pipe(t_cmd *cmd, char **envp, t_env *env_list)
{
    char    *path;

    path = get_cmd_path(cmd->argv[0], env_list);
    if (!path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->argv[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    execve(path, cmd->argv, envp);
    perror("minishell: execve");
    free(path);
    exit(126);
}

void    execute_pipe_child(t_cmd *cmd, int **pipes, int idx,
        int total, t_env **env_list, char **envp)
{
    signal_init_child();
    setup_pipe_redirections(pipes, idx, total);
    if (apply_redirections(cmd, envp) == -1)
        exit(1);
    if (is_builtin(cmd->argv[0]))
        exec_builtin_in_pipe(cmd, env_list);
    else
        exec_external_in_pipe(cmd, envp, *env_list);    
}

void    wait_for_children(t_cmd *cmd, pid_t *pids, int cmd_count)
{
    int status;
    int i;

    i = 0;
    while (i < cmd_count)
    {
        if (waitpid(pids[i], &status, 0) == -1)
        {
            perror("minishell: waitpid");
            i++;
            continue;
        }
        if (i == cmd_count -1)
        {
            if (WIFEXITED(status))
                cmd->ctx->exit.exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                cmd->ctx->exit.exit_status = 128 + WTERMSIG(status);
        }
        i++;
    }
}

void    fork_and_execute(t_cmd *cmd, int **pipes, pid_t *pids,
    t_pipes_ctx *pipe_ctx)
{
    int     i;
    t_cmd   *current;

    current = cmd;
    i = 0;
    while (current && i < pipe_ctx->cmd_count)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("minishell: fork");
            cmd->ctx->exit.exit_status = 1;
            break;
        }
        else if (pids[i] == 0)
            execute_pipe_child(current, pipes, i, pipe_ctx->cmd_count,
                pipe_ctx->env_list, pipe_ctx->env_array);
        close_parent_pipes(pipes, i, pipe_ctx->cmd_count);
        current = current->next;
        i++;
    }
}
