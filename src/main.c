/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 02:37:25 by moel-idr         ###   ########.fr       */
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
	if (prepare_heredocs(cmd, env_array) == -1 || apply_redirections(cmd,
			env_array) == -1)
	{
		signal_init_interactive();
		perror("redirection");
		return ;
	}
	execute_cmd(cmd, env_list);
	restore_stdio(saved_io[0], saved_io[1]);
	signal_init_interactive();
}

void	execute_single_cmd(t_cmd *cmd, t_env **env_list, char **env_array)
{
	int	saved_io[2];
	
	if (cmd->next)
	{
		execute_pipeline(cmd, env_list, env_array);
		return ;
	}
	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	if (!cmd || (!cmd->argv || !cmd->argv[0]))
	{
		if (cmd && cmd->redirect && cmd->redirect[0])
			prepare_heredocs(cmd, env_array);
		return;
	}
	if (is_builtin(cmd->argv[0]))
		exec_builtin_cmd(cmd, env_list, env_array, saved_io);
	else
	{
		if(prepare_heredocs(cmd, env_array) == -1 )
			exit(1);
		execute_externals(cmd, env_list);
	}
		
}

static void	process_input_line(char *input, char **env_array, t_env **env_list,
		t_ctx *ctx)
{
	t_cmd	*cmd;

	cmd = process_line(input, env_array, ctx);
	if (!cmd)
	{
		free(input);
		free_split(env_array);
		return ;
	}
	cmd->exit_status = ctx->exit.exit_status;
	cmd->ctx = ctx;
	execute_single_cmd(cmd, env_list, env_array);
	signal_check(cmd);
	clear_cmd(&cmd);
	free(input);
	free_split(env_array);
}

static void	handle_input_loop(t_env **env_list, char **env)
{
	char	*input;
	char	**env_array;
	t_ctx	ctx;

	(void)env;
	init_context(&ctx);
	while (1)
	{
		env_array = list_to_env(*env_list);
		input = read_complete_line();
		if (!input)
		{
			free_split(env_array);
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			ctx.exit.exit_status = 1;
			g_signal_received = 0;
		}
		process_input_line(input, env_array, env_list, &ctx);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = env_to_list(env);
	increment_shlvl(&env_list);
	handle_input_loop(&env_list, env);
	clear_history();
	free_env_list(env_list);
	return (0);
}
