/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:15:33 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/14 23:04:12 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "../src/Parsing/utils/libft/libft.h"
# include "./builtins.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>

# define REDD "\033[0;101m"
# define WHITE "\033[0;7m"
# define GREEN "\033[0;42m"
# define RED "\033[0;95m"
# define YELLOW "\033[0;33m"
# define SKYBLUE "\033[0;36m"
# define RESET "\033[0m"

extern volatile sig_atomic_t	g_signal_received;

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
typedef enum
{
	COMMAND, // done.          0
	CMD_ARG, // done            1
	OR,
	AND,
	SINGL_QU,  //               4
	DOUBLE_QU, //				5
	PIPE,      // done               6               8
	REDIR_IN,  // done           9
	REDIR_OUT, // done          10
	APPEND,    // done             11
	HERE_DOC,  // done           12
	FILE_NAME, // tbd
	VAR,
	QUOTED_VAR,
	CONCATENATED_VAR,
}					NodeType;

typedef struct s_token
{
	char			*value;
	char			*var_nam;
	NodeType		type;
	int				quote_flag;
	struct s_token	*next;
}					t_token;

typedef struct s_exit
{
	int				exit_status;
}					t_exit;

typedef struct s_ctx
{
	int				i;
	int				j;
	int				in_single;
	int				in_double;
	int				len;
	t_exit			exit;
}					t_ctx;

//t_cmd is defined in builtins.h

typedef struct s_heredoc
{
	char			*delimiter;
	char			**env;
	t_cmd			*cmd;
	int				i;
}					t_heredoc;

typedef struct s_process
{
	t_token			*head;
	t_token			*tail;
	t_token			*output;
	t_token			*expand;
	t_token			*wild;
	t_token			*strip;
	t_cmd			*cmd;
}					t_process;

typedef struct s_quote_ctx
{
	int	i;
	int	in_q;
	char	type;
	int	len;
}	t_quote_ctx;


int					is_space_unquoted(char *str, int index);

void				free_split(char **strs);
int					red_flag(t_token *token);
void				free_token_list(t_token *token);
int					token_has_quotes(t_token *token);
void				clear_cmd(t_cmd **head);
// int check_quotes(char *str);
// void err_handle(t_token *xpnd, char **envp); tf were you thinking!

void				print_system_error(char *context);
void				print_command_error(char *cmd, char *error_msg);
void				print_syntax_error(char *token);
void				print_file_error(char *filename);
void				print_ambiguous_redirect(char *var_name);
void				print_cmd_not_found(char *cmd);
t_token				*expanding_it(t_token *token, char **env);

void				append_list(t_token **head, t_token *new_node);

char				*strip_token(char *value);

int					pipe_err(t_token **list);
int					is_token_redirect(t_token *R);
int					is_it_doubled(t_token *dollar);
t_token				*stripper(t_token *xpnd);

t_token				*create_token(NodeType type, char *value, char *var_nam);
void				clear_tokens(t_token **head);
void				print_tokens(t_token *tokens);
t_token				*tokenizer(t_token **head, t_token **tail, char *input);
t_cmd				*store_cmds(t_token *token);
t_token				*expand_variables(t_token *tokens, char **envp);
t_cmd				*populate_cmd_data(t_cmd *cmd, t_token *token);
t_cmd				*build_cmd_list(t_token *token);

int					is_it_singled(t_token *dollar);

// void add_arg(t_trs *node, char *value);
// int is_operator(t_token *node);
// t_trs *create_node(char *value);
// char    *ft_strndup(const char *str, size_t n);

void				is_it_and(t_token **head, t_token **tail, int *i,
						char *input);
void				is_it_pipe(t_token **head, t_token **tail, int *i,
						char *input);
void				is_it_op(t_token **head, t_token **tail, int *i,
						char *input);
void				is_it_quote(t_token **head, t_token **tail, int *i,
						char *input, char c);
void				is_it_word(t_token **head, t_token **tail, int *i,
						char *input);
int					make_full_token(char *input, int len, int start,
						t_token **new);
void	get_full_quote(char *input, t_quote_ctx *ctx);
// void is_it_and(t_token **head, t_token **tail, int *i, char *input);

int					is_token_cmd(t_token *T);
int					is_token_redirect(t_token *R);
int					is_it_opp(t_token *op);
int					is_token_breaker(char c);
int					is_empty_string(t_token *token);
int					redir_check(t_token *token);

char				*replace_in_quotes(char *str, char **env);
char				*strip_str(char *str);
char				*handle_double(t_token *token, char **env);
int	handle_dollars(char *str, t_ctx *ctx, char *result, char **env);
int	replace_single_variable(char *str, t_ctx *ctx, char *result, char **env);
char				*expand(t_token *tokens, char **env);
char				*replace_in_arg(char *str, char **env);
int					is_it_var(char *str);
char				*var_name(char *str);
char				*get_env_value(char *name, char **env);
int					double_dollars(char *result, int j);
int					handle_token(t_token *xpnd, t_token **result,
						t_token *prev);
int					split_var_token(t_token *xpnd, t_token **result);
int	handle_expansion(char *str, char *result, t_ctx *ctx, char **env);
char				*remove_quotes(char *value);
int	replace_variable(char *str, t_ctx *ctx, char *result, char **env);
int					copy_token(t_token *xpnd, t_token **result);
int					redir_counter(t_token *token, NodeType stop_type);

// wild card -> bonus
t_token				*handel_wild_card(t_token *xpnd);
t_token				*make_list(t_token **result, int type, char *value,
						char *var_nam);
int					no_matches(char *token);
int					matched_count(char *token);
int					match_pattern(char *pattern, char *str);
char				**init_matches_array(int total_count);
char				**handle_no_expansion_case(char *token);
void				cleanup_matches_array(char **matches, int count);
int					should_skip_entry(struct dirent *entry, char *token);
int					add_match_to_array(char **matches, int count,
						char *filename);
int					collect_directory_matches(char *token, char **matches);
char	**handle_no_expansion_case(char *token);
char	**init_matches_array(int total_count);
void	cleanup_matches_array(char **matches, int count);
void				cleanup_expansion_results(char **res, int start_index);
int					process_wildcard_token(t_token *token, t_token **result);
int					process_regular_token(t_token *token, t_token **result);
char	**expand_wildcard(char *token, NodeType type);

// Builtins
int					execute_builtin(t_cmd *cmd, t_env **env);
void				execute_externals(t_cmd *cmd, t_env **env);
char				*get_cmd_path(char *cmd, t_env *env);
char				**list_to_env(t_env *list);

// redirections for execution
int					handle_out(char *file, int tr_ap, t_cmd *cmd);
int					has_quotes(char *str);
int					handle_in(char *file, t_cmd *cmd);
char				*get_next_line(int fd);
int					handle_heredoc(char *delimiter, char **env, t_cmd *cmd,
						int i);
int					apply_redirections(t_cmd *cmd, char **env);

// the main
char				*get_input(void);
void				free_token_lists(t_token **output, t_token **expand,
						t_token **wild, t_token **strip);
t_cmd				*process_line(char *input, char **env);
int					check_unclosed_quotes(const char *line);
char				*read_complete_line(void);
void				execute_cmd(t_cmd *cmd, t_env **env_list);
void				restore_stdio(int saved_stdin, int saved_stdout);
void				execute_single_cmd(t_cmd *cmd, t_env **env_list,
						char **env_array);
int					is_builtin(char *cmd);

// Signals 
void	signal_check(t_cmd *cmd);
void	signal_init_interactive(void);
void	signal_init_exec(void);
void	signal_init_heredoc(void);
void	signal_init_child(void);
void	signal_restore_default(void);
void	signal_reinit_after_fork(int context);
void	signal_handler_interactive(int signal);
void	signal_handler_heredoc(int signal);
int		is_signal_received(void);
void	reset_signal_received(void);


// main tester (to be removed)
void				print_parse(t_cmd *cmd);
void				print_tokens(t_token *tokens);



#endif