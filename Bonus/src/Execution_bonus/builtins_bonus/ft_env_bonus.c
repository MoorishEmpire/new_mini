/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:03 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 20:24:08 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

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
