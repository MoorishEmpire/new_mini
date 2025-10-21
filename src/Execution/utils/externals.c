/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 01:19:37 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 01:19:38 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_child(t_cmd *cmd, char *path, char **envp)
{
	signal_init_child();
	if (prepare_heredocs(cmd, envp) == -1 | apply_redirections(cmd, envp) == -1)
	{
		cleanup_resources(path, envp);
		exit(1);
	}
	if (ft_strchr(cmd->argv[0], '/'))
		execve(cmd->argv[0], cmd->argv, envp);
	else if (path)
		execve(path, cmd->argv, envp);
	perror("minishell");
	if (path)
		free(path);
	if (envp)
		free_split(envp);
	exit(126);
}

static void	handle_parent(t_cmd *cmd, pid_t pid, char *path, char **envp)
{
	int	status;

	waitpid(pid, &status, 0);
	handle_child_exit(status, cmd);
	cleanup_resources(path, envp);
}

static int	prepare_execution(t_cmd *cmd, char **path, char ***envp,
		t_env *env_list)
{
	*path = get_command_path(cmd, env_list);
	if (!is_valid_path(cmd, *path))
	{
		cleanup_resources(*path, NULL);
		return (0);
	}
	*envp = list_to_env(env_list);
	if (!(*envp))
	{
		cleanup_resources(*path, NULL);
		return (0);
	}
	return (1);
}

void	execute_externals(t_cmd *cmd, t_env **env_list)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (ft_strcmp(cmd->argv[0], "!") == 0 || ft_strcmp(cmd->argv[0], ":") == 0)
		return ;
	if (!prepare_execution(cmd, &path, &envp, *env_list))
		return ;
	signal_init_exec();
	pid = fork();
	if (pid == 0)
		handle_child(cmd, path, envp);
	else if (pid > 0)
		handle_parent(cmd, pid, path, envp);
	else
		handel_fork_error(cmd);
	signal_init_interactive();
}
