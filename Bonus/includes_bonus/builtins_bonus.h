/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:48:28 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 21:09:55 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

# include "structures_bonus.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

void	ft_echo(char **args, t_cmd *cmd);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_export(char **args, t_env **env, t_cmd *cmd);
int		ft_unset(char **args, t_env **env, t_cmd *cmd);
void	ft_exit(char **args, t_cmd *cmd);
int		ft_cd(char **args, t_env **env, t_cmd *cmd);
t_env	*env_to_list(char **env);
void	free_env_list(t_env *env);
void	update_env_var(t_env **env, char *var, char *value);
t_env	*copy_env_list(t_env *env);
int		is_valid_key(char *key);
char	*find_command_path(char *cmd);
char	**env_to_array(t_env *env);
void	sort_env_list(t_env **env);
char	*expand_tilde(char *path, t_env **env);
char	*cd_oldpwd_error(char *oldpwd, t_cmd *cmd);
char	*cd_home_error(char *oldpwd, t_cmd *cmd);
int		ft_strcmp(const char *s1, const char *s2);

#endif
