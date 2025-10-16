/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:32:27 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/16 21:29:55 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	replace_single_variable(char *str, t_ctx *ctx, char *result, char **env)
{
	int		start;
	int		k;
	char	*var;
	char	*val;

	start = ctx->i;
	while (str[ctx->i] && (ft_isalnum(str[ctx->i]) || str[ctx->i] == '_'))
		ctx->i++;
	var = ft_substr(str, start, ctx->i - start);
	val = get_env_value(var, env);
	k = 0;
	if (val)
	{
		while (val[k])
			result[ctx->j++] = val[k++];
	}
	free(var);
	free(val);
	return (ctx->j);
}

void	append_list(t_token **head, t_token *new_node)
{
	t_token	*temp;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

char *replace_in_arg(char *str, char **env, t_ctx *ctx)
{
    char *result;
    // Remove: t_ctx ctx;
    
    result = malloc(4096);
    if (!result)
        return (NULL);
    ctx->i = 0;  // Use arrow
    ctx->j = 0;
    while (str[ctx->i])
    {
        if (str[ctx->i] == '$')
            ctx->j = handle_dollars(str, ctx, result, env);  // Already correct
        else
            result[ctx->j++] = str[ctx->i++];
    }
    result[ctx->j] = '\0';
    return (result);
}

char *expand(t_token *tokens, char **env, t_ctx *ctx)
{
    char *var_val;

    var_val = NULL;
    var_val = replace_in_arg(tokens->value, env, ctx);  // Pass ctx
    return (var_val);
}
