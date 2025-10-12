NAME = minishell
LIBNAME = libmini.a
CC = gcc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Main files
files = 	src/Parsing/token src/main src/Parsing/parcer\
			src/Parsing/error_checks/pipe_err_check src/Parsing/error_checks/redirection_err\
			src/Parsing/error_checks/side_functions src/Parsing/wild_card/expand_wild\
			src/Parsing/tokenizer src/Parsing/var_expansion/arg_replace\
			src/Parsing/var_expansion/expanding src/Parsing/var_expansion/misc\
			src/Parsing/var_expansion/support src/Parsing/var_expansion/variables\
			src/Parsing/utils/helper_funcs/helps src/Parsing/quotes/quote_stripping\
			src/Parsing/wild_card/file_read src/Parsing/var_expansion/norm\
			src/Execution/builtins/builtins src/Execution/builtins/ft_cd\
			src/Execution/builtins/ft_echo src/Execution/builtins/ft_env\
			src/Execution/builtins/ft_export src/Execution/builtins/ft_exit\
			src/Execution/builtins/ft_pwd src/Execution/builtins/ft_unset\
			src/Execution/utils/ft_strcmp 

CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

LIBFT_DIR = src/Parsing/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBNAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
