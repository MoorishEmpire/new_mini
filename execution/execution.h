#ifndef EXECUTION_H
# define EXECUTION_H

# include "builtins.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

extern int			g_exit_status;

# define SUCCESS 0
# define FAILURE 1
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126

typedef struct s_cmd
{
	char			**argv;
	char			**redirect;
	char			**file;
	struct s_cmd	*next;
} 					t_cmd;

#endif
