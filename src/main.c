/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/13 19:11:42 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

t_env *g_env = NULL;
int g_exit_status = 0;

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	
	return (ft_strcmp(cmd, "echo") == 0 ||
			ft_strcmp(cmd, "cd") == 0 ||
			ft_strcmp(cmd, "pwd") == 0 ||
			ft_strcmp(cmd, "export") == 0 ||
			ft_strcmp(cmd, "unset") == 0 ||
			ft_strcmp(cmd, "env") == 0 ||
			ft_strcmp(cmd, "exit") == 0);
}

static void execute_cmd(t_cmd *cmd, t_env **env_list)
{

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;

    if (is_builtin(cmd->argv[0]))
    {
        execute_builtin(cmd, env_list);
        return;
    }
}

static void restore_stdio(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

void test_execute_single_cmd(t_cmd *cmd, t_env **env_list, char **env_array)
{
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;

    if (is_builtin(cmd->argv[0]))
    {
        if (apply_redirections(cmd, env_array) == -1)
        {
            perror("redirection");
            return;
        }
        execute_cmd(cmd, env_list);
        restore_stdio(saved_stdin, saved_stdout);
    }
    else
    {
        pid_t pid = fork();
        int status;

        if (pid == 0)
        {
            if (apply_redirections(cmd, env_array) == -1)
            {
                perror("redirection");
                exit(1);
            }
            execvp(cmd->argv[0], cmd->argv);
            perror("execvp failed");
            exit(1);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
            g_exit_status = WEXITSTATUS(status);
        }
        else
        {
            perror("fork failed");
        }
    }
}

void print_tokens(t_token *tokens)//just for testin
{
    while (tokens) {
        printf("\n\nToken is: %s\n"
				, tokens->value);
        tokens = tokens->next;
    }
}
void print_parse(t_cmd *cmd)
{
    int i;

	while (cmd)
	{
        i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf(RED "(commands) argv[%d]: %s\n" RESET, i, cmd->argv[i]);
			i++;
		}
		if (cmd->redirect && cmd->file)
		{
			i = 0;
			while (cmd->redirect[i] && cmd->file[i])
			{
				printf(YELLOW "Redirect[%d]: %s\n" RESET, i, cmd->redirect[i]);
				printf(SKYBLUE "File[%d]: %s\n" RESET, i, cmd->file[i]);
				printf("\n\n\n\n");
				i++;
			}
		}
		printf("----\n");
		cmd = cmd->next;
	}
}

void clear_tokens(t_token **head)
{
    t_token *tmp;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->value);  
        free(tmp); 
    }
}
void clear_cmd(t_cmd **head)
{
    t_cmd *tmp;
    int i;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
                free(tmp->argv[i++]);
            free(tmp->argv);
        }
        if (tmp->redirect)
        {
            i = 0;
            while (tmp->redirect[i])
                free(tmp->redirect[i++]);
            free(tmp->redirect);
        }
        if (tmp->file)
        {
            i = 0;
            while (tmp->file[i])
                free(tmp->file[i++]);
            free(tmp->file);
        }
        free(tmp);
    }
}
char *get_input(void)
{
    char *input = readline("\033[1;96m minishell > \033[0m");
    if (!input)
    {
        printf("exit\n");
        return NULL;
    }
    if (*input)
        add_history(input);
    return input;
}

void free_token_lists(t_token **output, t_token **expand,
                      t_token **wild, t_token **strip)
{
    if(output)
        clear_tokens(output);
    if(expand)
        clear_tokens(expand);
    
    clear_tokens(wild);
    clear_tokens(strip);
}

t_cmd *process_line(char *input, char **env)
{
    t_token *head   = NULL;
    t_token *tail   = NULL;
    t_token *output = NULL;
    t_token *expand = NULL;
    t_token *wild   = NULL;
    t_token *strip  = NULL;
    t_cmd   *cmd    = NULL;

    output = tokenizer(&head, &tail, input);
    expand = expanding_it(output, env);
    wild   = handel_wild_card(expand);
    strip  = stripper(wild);
    cmd    = build_cmd_list(strip);

	// print_tokens(output);
    free_token_lists(&output, &expand, &wild, &strip);

    return(cmd);
}
int check_unclosed_quotes(const char *line)
{
    int in_single = 0;
    int in_double = 0;
    int i = 0;

    while (line[i])
    {
        if (line[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (line[i] == '"' && !in_single)
            in_double = !in_double;
        i++;
    }
    return (in_single || in_double);
}
char *read_complete_line(void)
{
    char *line = readline("\033[1;96m minishell > \033[0m");
    if (!line)
    {
        printf("exit\n");
        return NULL;
    }
    if (*line)
        add_history(line);
    while (check_unclosed_quotes(line))
    {
        char *more = readline("> ");
        if (!more) 
        {
            printf("bash: unexpected EOF while looking for matching quote\n"
                    "bash: syntax error: unexpected end of file\n");
            free(line);
            return NULL;
        }
        char *tmp = ft_strjoin(line, "\n");
        char *joined = ft_strjoin(tmp, more);
        free(line);
        (free(tmp), free(more));
        line = joined;
    }
    return line;
}

int main(int ac, char **av, char **env)
{
    char    *input;
    t_cmd   *cmd;
    t_env   *env_list;
    char    **env_array;

    (void)ac;
    (void)av;

    env_list = env_to_list(env);

    while (1)
    {
        env_array = list_to_env(env_list);
        input = read_complete_line();
        if (!input)
            break;

        cmd = process_line(input, env_array);
        test_execute_single_cmd(cmd, &env_list,env);
        clear_cmd(&cmd);
        free(input);
	free_split(env_array);
    }
    clear_history();
    return 0;
}


