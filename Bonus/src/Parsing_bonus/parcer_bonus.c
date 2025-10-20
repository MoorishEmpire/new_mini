/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:57:08 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/minishell_bonus.h"

int	arg_count(t_token *token, NodeType i)
{
	int	j;

	j = 0;
	while (token && token->type != i)
	{
		j++;
		token = token->next;
	}
	return (j);
}

int	redir_counter(t_token *token, NodeType stop_type)
{
	int	count;

	count = 0;
	while (token && token->type != stop_type)
	{
		if (is_token_redirect(token))
			count++;
		token = token->next;
	}
	return (count);
}

t_cmd	*store_cmds(t_token *token)
{
	t_cmd	*cmd;
	int		redir_count;

	redir_count = redir_counter(token, PIPE);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		clear_tokens(&token);
		return (NULL);
	}
	cmd->argv = malloc(sizeof(char *) * (arg_count(token, PIPE) + 1));
	cmd->redirect = malloc(sizeof(char *) * (redir_count + 1));
	cmd->file = malloc(sizeof(char *) * (redir_count + 1));
	if (!cmd->argv || !cmd->redirect || !cmd->file)
		return (NULL);
	cmd->next = NULL;
	if (!populate_cmd_data(cmd, token))
	{
		free(cmd->file);
		free(cmd->argv);
		free(cmd->redirect);
		free(cmd->quoted_file);
		return (free(cmd), NULL);
	}
	return (cmd);
}

t_cmd	*build_cmd_list(t_token *token)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*cmd;

	head = NULL;
	cmd = NULL;
	tail = NULL;
	if (pipe_err(&token))
		return (NULL);
	while (token)
	{
		cmd = store_cmds(token);
		if (!cmd)
			return (NULL);
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}
