/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:03 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 20:23:47 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/minishell_bonus.h"

static int	handle_n_flag(char **args, int *nl)
{
	int	i;
	int	j;

	i = 1;
	*nl = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			*nl = 0;
		else
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(char **args, t_cmd *cmd)
{
	int	i;
	int	nl;

	i = handle_n_flag(args, &nl);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	cmd->ctx->exit.exit_status = 0;
}
