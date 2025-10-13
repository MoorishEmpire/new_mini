/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:58:03 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 20:19:42 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int has_quotes(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
			return(1);
		i++;
	}
	return(0);
}
int handle_heredoc(char *delimiter, char **env, t_cmd *cmd, int i)
{
    char *del;
    int fd[2];
    char *content;
    char *line;
    pid_t pid;

    if(pipe(fd) == -1)
        return(-1);
    
    pid = fork();
    if(pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return(-1);
    }
    
    if(pid == 0)
    {
        close(fd[0]);
        
        del = strip_str(delimiter);
		write(1,">",1);
        line = get_next_line(0);
        while(line)
        {
            size_t len = ft_strlen(line);
            if (len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            if (ft_strcmp(line, del) == 0)
            {
                free(line);
                break;
            }
            if(cmd->quoted_file[i] == 0)
                content = replace_in_arg(line, env);
            else
                content = ft_strdup(line);
            ft_putendl_fd(content, fd[1]);
            free(line);
            free(content);
			write(1,">",1);
            line = get_next_line(0);
        }
        close(fd[1]);
        free(del);
        exit(0);
    }
    
    close(fd[1]);
    waitpid(pid, NULL, 0);
    return(fd[0]);
}
