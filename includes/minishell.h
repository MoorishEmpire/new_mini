/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:15:33 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 21:12:07 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/Parsing/utils/libft/libft.h"
# include "./builtins.h"
# include "structures.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>

# define REDD "\033[0;101m"
# define WHITE "\033[0;7m"
# define GREEN "\033[0;42m"
# define RED "\033[0;95m"
# define YELLOW "\033[0;33m"
# define SKYBLUE "\033[0;36m"
# define RESET "\033[0m"

# define SUCCESS 0
# define FAILURE 1
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126

# define SIGNAL_INTERACTIVE 0
# define SIGNAL_EXEC 1
# define SIGNAL_HEREDOC 2
# define SIGNAL_CHILD 3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

extern volatile sig_atomic_t	g_signal_received;
int								is_space_unquoted(char *str, int index);
void							free_split(char **strs);
int								red_flag(t_token *token);
void							free_token_list(t_token *token);
int								token_has_quotes(t_token *token);
void							clear_cmd(t_cmd **head);
void							print_system_error(char *context);
void							print_command_error(char *cmd, char *error_msg);
void							print_syntax_error(char *token);
void							print_file_error(char *filename);
void							print_ambiguous_redirect(char *var_name);
void							print_cmd_not_found(char *cmd);
t_token							*expanding_it(t_token *token, char **env,
									t_ctx *ctx);
void							append_list(t_token **head, t_token *new_node);
char							*strip_token(char *value);
int								pipe_err(t_token **list, t_ctx *ctx);
int								is_token_redirect(t_token *R);
int								is_it_doubled(t_token *dollar);
t_token							*stripper(t_token *xpnd);
t_token							*create_token(t_nodetype type, char *value,
									char *var_nam);
void							clear_tokens(t_token **head);
void							print_tokens(t_token *tokens);
t_token							*tokenizer(t_token **head, t_token **tail,
									char *input);
t_cmd							*store_cmds(t_token *token, t_ctx *ctx);
t_token							*expand_variables(t_token *tokens, char **envp,
									t_ctx *ctx);
t_cmd							*populate_cmd_data(t_cmd *cmd, t_token *token,
									t_ctx *ctx);
t_cmd							*build_cmd_list(t_token *token, t_ctx *ctx);
int								is_it_singled(t_token *dollar);
void							exec_builtin_cmd(t_cmd *cmd, t_env **env_list,
									char **env_array, int saved_io[2]);
int								handle_redirect_only(t_cmd *cmd,
									char **env_array);
void							is_it_and(t_token **head, t_token **tail,
									int *i, char *input);
void							is_it_pipe(t_token **head, t_token **tail,
									int *i, char *input);
void							is_it_op(t_token **head, t_token **tail, int *i,
									char *input);
void							is_it_word(t_token **head, t_token **tail,
									int *i, char *input);
int								make_full_token(char *input, int len, int start,
									t_token **new);
void							get_full_quote(char *input, t_quote_ctx *ctx);
int								is_token_cmd(t_token *T);
int								is_token_redirect(t_token *R);
int								is_it_opp(t_token *op);
int								is_token_breaker(char c);
int								is_empty_string(t_token *token);
int								redir_check(t_token *token, t_ctx *ctx);
char							*replace_in_quotes(char *str, char **env,
									t_ctx *ctx);
char							*strip_str(char *str);
char							*handle_double(t_token *token, char **env,
									t_ctx *ctx);
int								handle_dollars(char *str, t_ctx *ctx,
									char *result, char **env);
int								replace_single_variable(char *str, t_ctx *ctx,
									char *result, char **env);
char							*expand(t_token *tokens, char **env,
									t_ctx *ctx);
char							*replace_in_arg(char *str, char **env,
									t_ctx *ctx);
int								is_it_var(char *str);
char							*var_name(char *str);
char							*get_env_value(char *name, char **env);
int								double_dollars(char *result, int j);
int								handle_token(t_token *xpnd, t_token **result,
									t_token *prev);
int								split_var_token(t_token *xpnd,
									t_token **result);
int								handle_expansion(char *str, char *result,
									t_ctx *ctx, char **env);
char							*remove_quotes(char *value);
int								replace_variable(char *str, t_ctx *ctx,
									char *result, char **env);
int								copy_token(t_token *xpnd, t_token **result);
int								redir_counter(t_token *token,
									t_nodetype stop_type);
t_token							*handel_wild_card(t_token *xpnd);
t_token							*make_list(t_token **result, int type,
									char *value, char *var_nam);
int								no_matches(char *token);
int								matched_count(char *token);
int								match_pattern(char *pattern, char *str);
char							**init_matches_array(int total_count);
char							**handle_no_expansion_case(char *token);
void							cleanup_matches_array(char **matches,
									int count);
int								should_skip_entry(struct dirent *entry,
									char *token);
int								add_match_to_array(char **matches, int count,
									char *filename);
int								collect_directory_matches(char *token,
									char **matches);
char							**handle_no_expansion_case(char *token);
char							**init_matches_array(int total_count);
void							cleanup_matches_array(char **matches,
									int count);
void							cleanup_expansion_results(char **res,
									int start_index);
int								process_wildcard_token(t_token *token,
									t_token **result);
int								process_regular_token(t_token *token,
									t_token **result);
char							**expand_wildcard(char *token, t_nodetype type);
int								execute_builtin(t_cmd *cmd, t_env **env);
char							*get_cmd_path(char *cmd, t_env *env);
char							**list_to_env(t_env *list);
char							*get_env(t_env *env, char *var);
void							increment_shlvl(t_env **env);
void							update_env_var(t_env **env, char *var,
									char *value);
void							free_env_list(t_env *env);
t_env							*copy_env_list(t_env *env);
void							lstenv_add_back(t_env **env, t_env *new_node);
void							sort_env_list(t_env **env);
t_env							*env_to_list(char **env);
char							**list_to_env(t_env *list);
void							execute_externals(t_cmd *cmd, t_env **env);
void							command_not_found(t_cmd *cmd);
int								validate_absolute_path(t_cmd *cmd);
int								is_valid_path(t_cmd *cmd, char *path);
void							handle_child_exit(int status, t_cmd *cmd);
void							cleanup_resources(char *path, char **envp);
void							handel_fork_error(t_cmd *cmd);
char							*get_command_path(t_cmd *cmd, t_env *env_list);
int								check_if_directory(const char *path,
									t_cmd *cmd);
int								check_permission(const char *path, t_cmd *cmd);
int								check_file_not_exist(t_cmd *cmd);
int								handle_out(char *file, int tr_ap, t_cmd *cmd);
int								has_quotes(char *str);
int								handle_in(char *file, t_cmd *cmd);
char							*get_next_line(int fd);
int								handle_heredoc(char *delimiter, char **env,
									t_cmd *cmd, int i);
int								apply_redirections(t_cmd *cmd, char **env);
int								prepare_heredocs(t_cmd *cmd, char **env);
char							*get_input(void);
void							init_context(t_ctx *ctx);
void							free_token_lists(t_token **o, t_token **x,
									t_token **s);
t_cmd							*process_line(char *input, char **env,
									t_ctx *ctx);
int								check_unclosed_quotes(const char *line);
char							*read_complete_line(void);
void							execute_cmd(t_cmd *cmd, t_env **env_list);
void							restore_stdio(int saved_stdin,
									int saved_stdout);
void							execute_single_cmd(t_cmd *cmd, t_env **env_list,
									char **env_array);
int								is_builtin(char *cmd);
void							signal_check(t_cmd *cmd);
void							signal_init_interactive(void);
void							signal_init_exec(void);
void							signal_init_heredoc(void);
void							signal_init_child(void);
void							signal_restore_default(void);
void							signal_reinit_after_fork(int context);
void							signal_handler_interactive(int signal);
void							signal_handler_heredoc(int signal);
int								is_signal_received(void);
void							reset_signal_received(void);
void							execute_pipeline(t_cmd *cmd, t_env **env_list,
									char **env_array);
void							exec_builtin_in_pipe(t_cmd *cmd,
									t_env **env_list);
void							exec_external_in_pipe(t_cmd *cmd, char **envp,
									t_env *env_mlist);
void							execute_pipe_child(t_cmd *cmd, int idx,
									t_pipeline *ctx);
void							wait_for_children(t_cmd *cmd, pid_t *pids,
									int cmd_count);
void							fork_and_execute(t_cmd *cmd, pid_t *pids,
									t_pipeline *ctx);
void							close_pipes(int **pipes, int pipe_count);
void							setup_pipe_redirections(int **pipes, int idx,
									int total, int has_output_redir);
void							close_parent_pipes(int **pipes, int idx,
									int total);
void							print_parse(t_cmd *cmd);
void							print_tokens(t_token *tokens);

#endif