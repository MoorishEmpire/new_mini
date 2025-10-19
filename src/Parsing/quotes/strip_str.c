#include "../../../includes/minishell.h"

static void	handle_quote(char *str, int *i, int *k, char *res)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		res[(*k)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
}

static void	copy_char(char *str, int *i, int *k, char *res)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		res[(*k)++] = str[(*i)++];
	}
	else
		res[(*k)++] = str[(*i)++];
}

char	*strip_str(char *str)
{
	char	*res;
	int		i;
	int		k;

	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quote(str, &i, &k, res);
		else
			copy_char(str, &i, &k, res);
	}
	res[k] = '\0';
	return (res);
}
