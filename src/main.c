/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 18:06:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0;

static void	execute_with_redirect(t_cmd *cmd, t_env **env_list,
			char **env_array)
{
	int	saved_io[2];

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	if (is_builtin(cmd->argv[0]))
		exec_builtin_cmd(cmd, env_list, env_array, saved_io);
	else
	{
		if (prepare_heredocs(cmd, env_array) == -1)
			exit(1);
		execute_externals(cmd, env_list);
		close(saved_io[0]);
		close(saved_io[1]);
	}
}

void	execute_single_cmd(t_cmd *cmd, t_env **env_list, char **env_array)
{
	if (cmd->next)
	{
		execute_pipeline(cmd, env_list, env_array);
		return ;
	}
	if (handle_redirect_only(cmd, env_array))
		return ;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	execute_with_redirect(cmd, env_list, env_array);
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
	update_env_var(&env_list, "OLDPWD", NULL);
	handle_input_loop(&env_list, env);
	clear_history();
	free_env_list(env_list);
	return (0);
}
