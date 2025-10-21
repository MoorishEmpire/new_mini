/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:37:06 by ael-most          #+#    #+#             */
/*   Updated: 2025/10/21 19:37:08 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
