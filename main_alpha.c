/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/20 19:40:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// Global environment variable
t_env *g_env = NULL;

void execute_cmd(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return;
    
    // Check if it's a built-in command
    if (is_builtin(cmd->argv[0]))
    {
        execute_builtin(cmd, &g_env);
        return;
    }
    
    // Execute external command
    pid_t pid;
    int status;
    char *cmd_path;
    
    pid = fork();
    if (pid == 0)
    {
        // Child processint			ft_pwd(void);
int			ft_env(t_env *env);
        if (cmd->redirect && cmd->file)
            apply_redirection(cmd);
        
        cmd_path = find_command_path(cmd->argv[0]);
        if (!cmd_path)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            exit(127);
        }
        
        if (execve(cmd_path, cmd->argv, env_to_array(g_env)) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        // Parent process
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
    }
    else
    {
        perror("fork");
        g_exit_status = 1;
    }
}

char *find_command_path(char *cmd)
{
    char *path;
    char **paths;
    char *full_path;
    int i;
    struct stat st;
    
    // If command contains '/', treat as absolute or relative path
    if (ft_strchr(cmd, '/'))
    {
        if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
            return (ft_strdup(cmd));
        return (NULL);
    }
    
    // Search in PATH
    path = get_env(g_env, "PATH");
    if (!path)
        return (NULL);
    
    paths = ft_split(path, ':');
    free(path);
    if (!paths)
        return (NULL);
    
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        
        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free_split(paths);
            return (full_path);
        }
        
        free(full_path);
        i++;
    }
    
    free_split(paths);
    return (NULL);
}

char **env_to_array(t_env *env)
{
    t_env *tmp;
    char **array;
    int count;
    int i;
    
    count = 0;
    tmp = env;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);
    
    i = 0;
    tmp = env;
    while (tmp)
    {
        if (tmp->value)
        {
            array[i] = ft_strjoin(tmp->var, "=");
            array[i] = ft_strjoin(array[i], tmp->value);
        }
        else
            array[i] = ft_strdup(tmp->var);
        i++;
        tmp = tmp->next;
    }
    array[count] = NULL;
    
    return (array);
}

void print_tokens(t_token *tokens)//just for testing
{
    while (tokens) {
        printf("\n\nToken is: %s\n"
				, tokens->value);
        tokens = tokens->next;
    }
}
void print_parse(t_cmd *cmd)//just for testing 
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
    char *input;
    t_cmd *cmd;

    (void)ac;
    (void)av;

    // Initialize global environment
    g_env = env_to_list(env);
    if (!g_env)
    {
        perror("Failed to initialize environment");
        return (1);
    }

    // Initialize exit status
    g_exit_status = 0;

    while (1)
    {
        input = read_complete_line();
        if (!input)
            break;

        cmd = process_line(input, env);
        if (cmd)
        {
            execute_cmd(cmd);
            clear_cmd(&cmd);
        }
        free(input);
    }
    
    // Cleanup
    clear_history();
    free_env_list(g_env);
    return (g_exit_status);
}


