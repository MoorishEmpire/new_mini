#ifndef BUILTINS_H
# define BUILTINS_H

# include <libft/libft.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <limits.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
} 					t_env;

extern int			g_exit_status;

int					ft_pwd(void);
int					ft_env(t_env *env);
void				ft_echo(char **args);
void				ft_exit(char **args);
int					ft_cd(char **args, t_env **env);
int					ft_unset(char **args, t_env **env);
int					ft_export(char **args, t_env **env);

void				free_2d_arr(char **ptr);
int					is_valid_key(char *key);
int					ft_atoi(const char *str);
t_env				*env_to_list(char **env);
char				**list_to_env(t_env *list);
void				ft_putstr_fd(char *s, int fd);
char				*get_env_value(t_env *env, const char *key);
char				*ft_strchr(const char *string, int searchedChar);
void				update_env_var(t_env **env, const char *key, const char *value);
int					ft_strncmp(char *first, char *second, size_t length);
char				*get_cmd_path(char *cmd, t_env *env);

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);

#endif