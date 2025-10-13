/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:13:58 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 20:29:00 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int apply_redirections(t_cmd *cmd, char **env)
{
    int i;
    int last_heredoc_fd = -1;

    i = 0;
    while(cmd->redirect[i])
    {
        if(ft_strncmp(cmd->redirect[i],">",2) == 0)
            if(handle_out(cmd->file[i],0) == -1)
                return(-1);
        if(ft_strncmp(cmd->redirect[i],">>",2) == 0)
            if(handle_out(cmd->file[i],1) == -1)
                return(-1);
        if(ft_strncmp(cmd->redirect[i],"<",2) == 0)
            if(handle_in(cmd->file[i]) == -1)
                return(-1);
        if(ft_strncmp(cmd->redirect[i],"<<",2) == 0)
        {
            if(last_heredoc_fd != -1)
                close(last_heredoc_fd);
            last_heredoc_fd = handle_heredoc(cmd->file[i],env,cmd,i);
            if(last_heredoc_fd == -1)
                return(-1);
        }
        i++;  
    }
    if(last_heredoc_fd != -1)
    {
        if(dup2(last_heredoc_fd, STDIN_FILENO) == -1)
            return(perror("minishell: dup2"), -1);
        close(last_heredoc_fd);
    }
    return (0);
}
