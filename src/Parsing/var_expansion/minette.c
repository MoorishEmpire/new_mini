/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/16 21:22:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_question_mark(char *str, t_ctx *ctx, char *result)
{
	char	*status;
	int		k;

	if (str[ctx->i] == '?')
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
	char	*var_name;
	char	*var_value;
	int		start;

	start = ctx->i;
	while (str[ctx->i] && (ft_isalnum(str[ctx->i]) || str[ctx->i] == '_'))
		ctx->i++;
	if (ctx->i == start)
	{
		result[ctx->j++] = '$';
		return (ctx->j);
	}
	var_name = ft_substr(str, start, ctx->i - start);
	var_value = get_env_value(var_name, env);
	free(var_name);
	if (!var_value)
		return (ctx->j);

	int k = 0;
	while (var_value[k])
		result[ctx->j++] = var_value[k++];
	free(var_value);
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
