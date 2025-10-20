/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:32:40 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/20 22:56:27 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/minishell_bonus.h"

void	clear_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->value);
		free(tmp);
	}
}

char	*get_input(void)
{
	char	*input;

	input = readline("\033[1;96m minishell > \033[0m");
	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_token_lists(t_token **o, t_token **x, t_token **w, t_token **s)
{
	if (o)
		clear_tokens(o);
	if (x)
		clear_tokens(x);
	clear_tokens(w);
	clear_tokens(s);
}

void	clear_cmd(t_cmd **head)
{
	t_cmd	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free_str_array(tmp->argv);
		free_str_array(tmp->redirect);
		free_str_array(tmp->file);
		free(tmp->quoted_file);
		free(tmp);
	}
}
