/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:32:47 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 16:53:29 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

t_cmd	*process_line(char *input, char **env, t_ctx *ctx)
{
	t_process	p;
	t_cmd		*temp;

	p.head = NULL;
	p.tail = NULL;
	p.output = NULL;
	p.expand = NULL;
	p.strip = NULL;
	p.cmd = NULL;
	p.output = tokenizer(&p.head, &p.tail, input);
	p.expand = expanding_it(p.output, env, ctx);
	p.strip = stripper(p.expand);
	p.cmd = build_cmd_list(p.strip,ctx);
	temp = p.cmd;
	while (temp)
	{
		temp->ctx = ctx;
		temp = temp->next;
	}
	free_token_lists(&p.output, &p.expand, &p.strip);
	return (p.cmd);
}

static char	*handle_unexpected_eof(char *line)
{
	printf("bash: unexpected EOF while looking for matching quote\n");
	printf("bash: syntax error: unexpected end of file\n");
	free(line);
	return (NULL);
}

static char	*read_until_closed_quotes(char *line)
{
	char	*more;
	char	*tmp;
	char	*joined;

	while (check_unclosed_quotes(line))
	{
		more = readline("> ");
		if (!more)
			return (handle_unexpected_eof(line));
		tmp = ft_strjoin(line, "\n");
		joined = ft_strjoin(tmp, more);
		free(line);
		free(tmp);
		free(more);
		line = joined;
	}
	return (line);
}

char	*read_complete_line(void)
{
	char	*line;

	line = readline("\033[1;96m minishell > \033[0m");
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	line = read_until_closed_quotes(line);
	return (line);
}
