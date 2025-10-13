/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:13:58 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 18:26:11 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int apply_redirections(t_cmd *cmd, char **env)
{
    int i;

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
            cmd->here_fd = handle_heredoc(cmd->file[i],env,cmd,i);
            if(cmd->here_fd == -1)
                return(-1);
            if(dup2(cmd->here_fd, STDIN_FILENO) == -1)
                return(perror("minishell: dup2"), -1);
            close(cmd->here_fd);
        }
        i++;  
    }
    return (0);
}

