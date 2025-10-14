/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 19:34:03 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

t_env		*g_env = NULL;
int			g_exit_status = 0;

static void	exec_builtin_cmd(t_cmd *cmd, t_env **env_list, char **env_array,
		int saved_io[2])
{
	if (apply_redirections(cmd, env_array) == -1)
	{
		perror("redirection");
		return ;
	}
	execute_cmd(cmd, env_list);
	restore_stdio(saved_io[0], saved_io[1]);
}

static void	exec_external_cmd(t_cmd *cmd, char **env_array)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd, env_array) == -1)
		{
			perror("redirection");
			exit(1);
		}
		execvp(cmd->argv[0], cmd->argv);
		perror("execvp failed");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork failed");
}

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
		exec_external_cmd(cmd, env_array);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;
	t_env	*env_list;
	char	**env_array;

	(void)ac;
	(void)av;
	env_list = env_to_list(env);
	while (1)
	{
		env_array = list_to_env(env_list);
		input = read_complete_line();
		if (!input)
			break ;
		cmd = process_line(input, env_array);
		execute_single_cmd(cmd, &env_list, env);
		clear_cmd(&cmd);
		free(input);
		free_split(env_array);
	}
	clear_history();
	return (0);
}
