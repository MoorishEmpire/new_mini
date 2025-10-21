/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:07:06 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/21 21:07:07 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum s_node
{
	COMMAND,
	CMD_ARG,
	OR,
	AND,
	SINGL_QU,
	DOUBLE_QU,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	FILE_NAME,
	VAR,
	QUOTED_VAR,
	CONCATENATED_VAR,
}					t_nodetype;

typedef struct s_token
{
	char			*value;
	char			*var_nam;
	t_nodetype		type;
	int				quote_flag;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

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

typedef struct s_cmd
{
	char			**argv;
	char			**redirect;
	char			**file;
	struct s_cmd	*next;
	int				here_fd;
	int				redir_in_fd;
	int				redir_out_fd;
	int				*quoted_file;
	int				exit_status;
	t_ctx			*ctx;
}					t_cmd;

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
	t_token			*strip;
	t_cmd			*cmd;
}					t_process;

typedef struct s_quote_ctx
{
	int				i;
	int				in_q;
	char			type;
	int				len;
}					t_quote_ctx;

typedef struct s_pipes_ctx
{
	int				cmd_count;
	t_env			**env_list;
	char			**env_array;
}					t_pipes_ctx;

typedef struct s_pipeline
{
	int				**pipes;
	int				cmd_count;
	t_env			**env_list;
	char			**env_array;
}					t_pipeline;

#endif