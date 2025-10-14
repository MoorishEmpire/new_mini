/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 19:15:53 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_question_mark(char *str, t_ctx *ctx, char *result)
{
	char	*status;
	int		k;

	if (str[ctx->i] == '?' && (ctx->exit.exit_status || 1))
	{
		status = ft_itoa(ctx->exit.exit_status);
		k = 0;
		while (status[k])
			result[ctx->j++] = status[k++];
		free(status);
		ctx->i++;
		return (1);
	}
	return (0);
}

int	handle_variable_or_dollar(char *str, t_ctx *ctx, char *result, char **env)
{
	if (str[ctx->i] && (ft_isalnum(str[ctx->i]) || str[ctx->i] == '_'))
		ctx->j = replace_single_variable(str, ctx, result, env);
	else
		result[ctx->j++] = '$';
	return (ctx->j);
}

int	handle_dollars(char *str, t_ctx *ctx, char *result, char **env)
{
	int	count;
	int	mod;

	count = 0;
	while (str[ctx->i + count] == '$')
		count++;
	mod = count / 2;
	while (mod--)
		ctx->j = double_dollars(result, ctx->j);
	if (count % 2 == 1)
	{
		ctx->i += count;
		if (handle_question_mark(str, ctx, result))
			return (ctx->j);
		ctx->j = handle_variable_or_dollar(str, ctx, result, env);
	}
	else
		ctx->i += count;
	return (ctx->j);
}
