/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:58:03 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 20:34:54 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*process_lines(char *line, char **env, t_cmd *cmd, int i)
{
	char	*content;

	if (cmd->quoted_file[i] == 0)
		content = replace_in_arg(line, env);
	else
		content = ft_strdup(line);
	return (content);
}

void	heredoc_child_loop(int fd, t_heredoc *h)
{
	char	*line;
	char	*content;
	size_t	len;

	write(1, ">", 1);
	line = get_next_line(0);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, h->delimiter) == 0)
		{
			free(line);
			break ;
		}
		content = process_lines(line, h->env, h->cmd, h->i);
		ft_putendl_fd(content, fd);
		free(line);
		free(content);
		write(1, ">", 1);
		line = get_next_line(0);
	}
}

int	handle_heredoc(char *delimiter, char **env, t_cmd *cmd, int i)
{
	char		*del;
	int			fd[2];
	pid_t		pid;
	t_heredoc	h;

	if (pipe(fd) == -1)
		return (-1);
	signal_init_exec();
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		signal_init_interactive();
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		signal_init_heredoc();
		del = strip_str(delimiter);
		h.delimiter = del;
		h.env = env;
		h.cmd = cmd;
		h.i = i;
		(heredoc_child_loop(fd[1], &h), close(fd[1]), free(del), exit(0));
	}
	return (close(fd[1]), waitpid(pid, NULL, 0),signal_init_interactive(), fd[0]);
}
