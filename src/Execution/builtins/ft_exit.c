#include "../../../includes/minishell.h"

static int	is_nbr(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	safe_atoi_exit(const char *str)
{
	long long	val;
	int			i;
	int			sign;

	val = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (val > (LONG_MAX - (str[i] - '0')) / 10)
		{
			(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd((char *)str, 2));
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		val = val * 10 + (str[i] - '0');
		i++;
	}
	return (val * sign);
}

static int	handel_args(char **args, t_cmd *cmd)
{
	long long	val;

	val = 0;
	if (!is_nbr(args[1]))
	{
		(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(args[1], 2));
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		cmd->ctx->exit.exit_status = 1;
		return (-1);
	}
	val = safe_atoi_exit(args[1]);
	return (val % 256);
}

void	ft_exit(char **args, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1])
	{
		exit_code = handel_args(args, cmd);
		if (exit_code == -1)
			return ;
	}
	else
		exit_code = cmd->ctx->exit.exit_status;
	clear_history();
	exit(exit_code);
}
