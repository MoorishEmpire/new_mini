NAME = minishell
LIBNAME = libmini.a
CC = gcc
READLINE_DIR = ./readline-8.2.13

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(READLINE_DIR)/include
LDFLAGS = -L$(READLINE_DIR)/lib -lreadline

# Main files
files = 	src/Parsing/token src/main src/Parsing/parcer\
			src/Parsing/error_checks/pipe_err_check src/Parsing/error_checks/redirection_err\
			src/Parsing/error_checks/side_functions src/Parsing/wild_card/expand_wild\
			src/Parsing/tokenizer src/Parsing/var_expansion/arg_replace src/Parsing/parser_sup\
			src/Parsing/var_expansion/expanding src/Parsing/var_expansion/misc\
			src/Parsing/var_expansion/support src/Parsing/var_expansion/variables\
			src/Parsing/utils/helper_funcs/helps src/Parsing/quotes/quote_stripping src/Parsing/quotes/strip_str\
			src/Parsing/wild_card/file_read src/Parsing/var_expansion/norm src/Parsing/var_expansion/xpnd_handle\
			src/Execution/builtins/builtins src/Execution/builtins/ft_cd\
			src/Execution/builtins/ft_echo src/Execution/builtins/ft_env\
			src/Execution/builtins/ft_export src/Execution/builtins/ft_exit\
			src/Execution/builtins/ft_pwd src/Execution/builtins/ft_unset\
			src/Execution/utils/ft_strcmp src/Execution/redirection/get_input\
			src/Execution/redirection/get_next_line src/Execution/redirection/here_doc_handle\
			src/Execution/redirection/redir_handle src/main_funcs/main_misc\
			src/main_funcs/main_support src/main_funcs/main_test src/main_funcs/main_exec\
			src/Parsing/wild_card/wild_help src/Parsing/wild_card/wild_misc src/Parsing/var_expansion/minette\
			src/Execution/signals/signals src/Execution/signals/signal_helper src/Execution/signals/signal_helper1\
			src/Execution/utils/externals src/Execution/utils/externals_helper\
			src/Execution/pipes/pipe src/Execution/pipes/pipe_utils src/Execution/pipes/pipe_utils2\
			src/Execution/utils/env src/Execution/utils/env_helpers\
			src/Execution/utils/externals_utils src/Execution/utils/signals_utils2
			
CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

LIBFT_DIR = src/Parsing/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Header files
HEADERS = includes/minishell.h includes/builtins.h includes/structures.h

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(emo)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "\033[0;32m✅ Compilation successful!\033[0m"

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "\033[0;33m🧹 Cleaned object files.\033[0m"

fclean: clean
	@rm -f $(NAME) $(LIBNAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "\033[0;33m🧹 Fully cleaned project.\033[0m"

re: fclean all

.PHONY: all clean fclean re

define emo
	@echo "\033[0;91m"
	@echo "	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"
	@echo "	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║"
	@echo "	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║"
	@echo "	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"
	@echo "	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "\033[0;32m"
	@echo "\t   ____                     _                           _    "
	@echo "\t  | __ ) _   _    __ _ ___ | |      _ __ ___   ___  ___| |_  "
	@echo "\t  |  _ \| | | |  / _\`|/ _ \  |_____| '\''_  \\ / _ \/ __| __| "
	@echo "\t  | |_) | |_| | | (_| |  __/ |_____| | | | | | (_) \__ \ |_  "
	@echo "\t  |____/ \__, |  \__,_|\___|_|     |_| |_| |_|\___/|___/\__| "
	@echo "\t         |___/                                               "
	@echo "\033[0m"
	@echo "\033[0;32m"
	@echo "\t   ___    "
	@echo "\t  ( _ )   "
	@echo "\t  / _ \\\\/\\ "
	@echo "\t  | (_>  < "
	@echo "\t  \\___/\\/ "
	@echo "\033[0;32m"
	@echo "	                       _       _     _      "
	@echo "	  _ __ ___   ___   ___| |     (_) __| |_ __ "
	@echo "	 | '_ \` _ \\ / _ \\ / _ \\ |_____| |/ _\` | '__|"
	@echo "	 | | | | | | (_) |  __/ |_____| | (_| | |   "
	@echo "	 |_| |_| |_|\\___/ \\___|_|     |_|\\__,_|_|   "
	@echo "\033[0;33m"
	@echo "	  _ ____________    __  __ ___ ___  "
	@echo "	 / |__ /__ /__  |  |  \\/  | __|   \\ "
	@echo "	 | ||_ \\|_ \\ / /   | |\\/| | _|| |) |"
	@echo "	 |_|___/___//_/    |_|  |_|___|___/ "
	@echo "\033[0m"
endef