/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:18:11 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 22:24:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_argv_on_error(t_cmd *cmd, int *i)
{
	while (*i > 0)
		free(cmd->argv[--(*i)]);
}

int	handle_redirect(t_cmd *cmd, t_token **token, int *j, int *i)
{
	cmd->redirect[*j] = ft_strdup((*token)->value);
	*token = (*token)->next;
	if (redir_check(*token))
	{
		free(cmd->redirect[*j]);
		cmd->redirect[*j] = NULL;
		free_argv_on_error(cmd, i);
		return (0);
	}
	cmd->file[*j] = ft_strdup((*token)->value);
	cmd->quoted_file[*j] = (*token)->quote_flag;
	(*j)++;
	return (1);
}

int	fill_cmd_parts(t_cmd *cmd, t_token *token, int *i, int *j)
{
	while (token && token->type != PIPE)
	{
		if (is_token_cmd(token))
			cmd->argv[(*i)++] = ft_strdup(token->value);
		else if (is_token_redirect(token))
		{
			if (!handle_redirect(cmd, &token, j, i))
				return (0);
		}
		token = token->next;
	}
	return (1);
}

t_cmd	*populate_cmd_data(t_cmd *cmd, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd->quoted_file = malloc(sizeof(int) * (redir_counter(token, PIPE) + 1));
	if (!fill_cmd_parts(cmd, token, &i, &j))
		return (NULL);
	cmd->argv[i] = NULL;
	cmd->redirect[j] = NULL;
	cmd->file[j] = NULL;
	return (cmd);
}
