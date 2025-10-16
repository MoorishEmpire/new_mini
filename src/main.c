/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/16 22:19:01 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0;

static void	exec_builtin_cmd(t_cmd *cmd, t_env **env_list, char **env_array,
		int saved_io[2])
{
	signal_init_exec();
	if (apply_redirections(cmd, env_array) == -1)
	{
		signal_init_interactive();
		perror("redirection");
		return ;
	}
	execute_cmd(cmd, env_list);
	restore_stdio(saved_io[0], saved_io[1]);
	signal_init_interactive();
}

/*
static void	exec_external_cmd(t_cmd *cmd, char **env_array)
{
	pid_t	pid;
	int		status;
	char	*path;

	signal_init_exec();
	pid = fork();
	if (pid == 0)
	{
		signal_init_child();
		if (apply_redirections(cmd, env_array) == -1)
		{
			perror("redirection");
			exit(1);
		}
		execvp(path, cmd->argv);
		perror("execvp failed");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		cmd->ctx->exit.exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork failed");
	signal_init_interactive();
}
*/

void	execute_single_cmd(t_cmd *cmd, t_env **env_list, char **env_array)
{
	int	saved_io[2];

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
		exec_builtin_cmd(cmd, env_list, env_array, saved_io);
	else
		execute_externals(cmd, env_list);
		
}

int main(int ac, char **av, char **env)
{
    t_cmd *cmd;
    char *input;
    t_env *env_list;
    char **env_array;
    t_ctx ctx;

    (void)ac;
    (void)av;

    env_list = env_to_list(env);
    ctx.exit.exit_status = 0;
    signal_init_interactive();
    while (1)
    {
        env_array = list_to_env(env_list);
        input = read_complete_line();
        if (!input)
        {
            free_split(env_array);
            break ;
        }
        
        // Check for Ctrl+C at interactive prompt FIRST
        if (g_signal_received == SIGINT)
        {
            ctx.exit.exit_status = 1;
            g_signal_received = 0;
        }
        
        cmd = process_line(input, env_array, &ctx);
        if (!cmd)
        {
            free(input);
            free_split(env_array);
            continue ;
        }
        cmd->exit_status = ctx.exit.exit_status;
        cmd->ctx = &ctx;
        execute_single_cmd(cmd, &env_list, env);
        signal_check(cmd);  // This handles Ctrl+C during execution (130)
        clear_cmd(&cmd);
        free(input);
        free_split(env_array);
    }
    clear_history();
    free_env_list(env_list);
    return (0);
}