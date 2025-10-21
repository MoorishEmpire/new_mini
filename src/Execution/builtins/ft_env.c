/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:37 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:36:39 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->var)
			printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
	return (0);
}
