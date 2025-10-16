/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpnd_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/16 21:31:59 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_exit_status(char *result, t_ctx *ctx)
{
	char	*status;
	int		k;

	status = ft_itoa(ctx->exit.exit_status);
	k = 0;
	while (status[k])
		result[ctx->j++] = status[k++];
	free(status);
	ctx->i += 2;
	return (1);
}

static int	should_expand(char *str, t_ctx *ctx, char c)
{
	if (str[ctx->i] != '$' || ctx->in_single)
		return (0);
	if (str[ctx->i + 1] == c)
		return (1);
	return (0);
}

static int	handle_double_dollar(char *result, t_ctx *ctx)
{
	ctx->j = double_dollars(result, ctx->j);
	ctx->i += 2;
	return (1);
}

static int	handle_dollar_quote(t_ctx *ctx)
{
	ctx->i++;
	return (1);
}

int	handle_expansion(char *str, char *result, t_ctx *ctx, char **env)
{
	if (should_expand(str, ctx, '?'))
		return (handle_exit_status(result, ctx));
	if (should_expand(str, ctx, '$'))
		return (handle_double_dollar(result, ctx));
	if (should_expand(str, ctx, '"'))
		return (handle_dollar_quote(ctx));
	if (str[ctx->i] == '$' && !ctx->in_single && (ft_isalnum(str[ctx->i + 1])
			|| str[ctx->i + 1] == '_'))
	{
		ctx->j = replace_variable(str, ctx, result, env);
		return (1);
	}
	return (0);
}
