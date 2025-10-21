NAME = minishell
BONUS_NAME = minishell_bonus
LIBNAME = libmini.a
CC = gcc
READLINE_DIR = ./readline-8.2.13

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(READLINE_DIR)/include
LDFLAGS = -L$(READLINE_DIR)/lib -lreadline

# Main files
files = 	src/Parsing/token src/main src/Parsing/parcer\
			src/Parsing/error_checks/pipe_err_check src/Parsing/error_checks/redirection_err\
			src/Parsing/error_checks/side_functions\
			src/Parsing/tokenizer src/Parsing/var_expansion/arg_replace src/Parsing/parser_sup\
			src/Parsing/var_expansion/expanding src/Parsing/var_expansion/misc\
			src/Parsing/var_expansion/support src/Parsing/var_expansion/variables\
			src/Parsing/utils/helper_funcs/helps src/Parsing/quotes/quote_stripping src/Parsing/quotes/strip_str\
			src/Parsing/var_expansion/norm src/Parsing/var_expansion/xpnd_handle\
			src/Execution/builtins/builtins src/Execution/builtins/ft_cd src/Execution/builtins/cd_helper\
			src/Execution/builtins/ft_echo src/Execution/builtins/ft_env\
			src/Execution/builtins/ft_export src/Execution/builtins/ft_exit\
			src/Execution/builtins/ft_pwd src/Execution/builtins/ft_unset\
			src/Execution/utils/ft_strcmp src/Execution/redirection/get_input\
			src/Execution/redirection/get_next_line src/Execution/redirection/here_doc_handle\
			src/Execution/redirection/redir_handle src/main_funcs/main_misc\
			src/main_funcs/main_support src/main_funcs/main_test src/main_funcs/main_exec\
			src/Parsing/var_expansion/minette src/Execution/utils/exec_sup\
			src/Execution/signals/signals src/Execution/signals/signal_helper src/Execution/signals/signal_helper1\
			src/Execution/utils/externals src/Execution/utils/externals_helper\
			src/Execution/pipes/pipe src/Execution/pipes/pipe_utils src/Execution/pipes/pipe_utils2\
			src/Execution/utils/env src/Execution/utils/env_helpers src/Execution/pipes/pipe_helper\
			src/Execution/utils/externals_utils src/Execution/utils/signals_utils2\

# Bonus files
b_files = Bonus/src/Parsing_bonus/token_bonus \
          Bonus/src/main_bonus \
          Bonus/src/Parsing_bonus/parcer_bonus \
          Bonus/src/Parsing_bonus/error_checks_bonus/pipe_err_check_bonus \
          Bonus/src/Parsing_bonus/error_checks_bonus/redirection_err_bonus \
          Bonus/src/Parsing_bonus/error_checks_bonus/side_functions_bonus \
          Bonus/src/Parsing_bonus/wild_card_bonus/expand_wild_bonus \
          Bonus/src/Parsing_bonus/tokenizer_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/arg_replace_bonus \
          Bonus/src/Parsing_bonus/parser_sup_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/expanding_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/misc_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/support_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/variables_bonus \
          Bonus/src/Parsing_bonus/utils_bonus/helper_funcs_bonus/helps_bonus \
          Bonus/src/Parsing_bonus/quotes_bonus/quote_stripping_bonus \
          Bonus/src/Parsing_bonus/quotes_bonus/strip_str_bonus \
          Bonus/src/Parsing_bonus/wild_card_bonus/file_read_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/norm_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/xpnd_handle_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/builtins_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_cd_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/cd_helper_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_echo_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_env_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_export_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_exit_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_pwd_bonus \
          Bonus/src/Execution_bonus/builtins_bonus/ft_unset_bonus \
          Bonus/src/Execution_bonus/utils_bonus/ft_strcmp_bonus \
          Bonus/src/Execution_bonus/redirection_bonus/get_input_bonus \
          Bonus/src/Execution_bonus/redirection_bonus/get_next_line_bonus \
          Bonus/src/Execution_bonus/redirection_bonus/here_doc_handle_bonus \
          Bonus/src/Execution_bonus/redirection_bonus/redir_handle_bonus \
          Bonus/src/main_funcs_bonus/main_misc_bonus \
          Bonus/src/main_funcs_bonus/main_support_bonus \
          Bonus/src/main_funcs_bonus/main_test_bonus \
          Bonus/src/main_funcs_bonus/main_exec_bonus \
          Bonus/src/Parsing_bonus/wild_card_bonus/wild_help_bonus \
          Bonus/src/Parsing_bonus/wild_card_bonus/wild_misc_bonus \
          Bonus/src/Parsing_bonus/var_expansion_bonus/minette_bonus \
          Bonus/src/Execution_bonus/signals_bonus/signals_bonus \
          Bonus/src/Execution_bonus/signals_bonus/signal_helper_bonus \
          Bonus/src/Execution_bonus/signals_bonus/signal_helper1_bonus \
          Bonus/src/Execution_bonus/utils_bonus/externals_bonus \
          Bonus/src/Execution_bonus/utils_bonus/externals_helper_bonus \
          Bonus/src/Execution_bonus/pipes_bonus/pipe_bonus \
          Bonus/src/Execution_bonus/pipes_bonus/pipe_utils_bonus \
          Bonus/src/Execution_bonus/pipes_bonus/pipe_utils2_bonus \
          Bonus/src/Execution_bonus/utils_bonus/env_bonus \
          Bonus/src/Execution_bonus/utils_bonus/env_helpers_bonus \
          Bonus/src/Execution_bonus/pipes_bonus/pipe_helper_bonus \
          Bonus/src/Execution_bonus/utils_bonus/externals_utils_bonus \
          Bonus/src/Execution_bonus/utils_bonus/signals_utils2_bonus\

# Object files
CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

CFILES_B = $(b_files:%=%.c)
OBJS_B = $(b_files:%=%.o)

LIBFT_DIR = src/Parsing/utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Header files
HEADERS = includes/minishell.h includes/builtins.h includes/structures.h

#bonus headers
BONUS_HEADERS = Bonus/includes_bonus/minishell_bonus.h Bonus/includes_bonus/builtins_bonus.h Bonus/includes_bonus/structures_bonus.h

all: $(NAME)

# Mandatory compilation
$(NAME): $(OBJS) $(LIBFT)
	$(emo)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "\033[0;32m✅ Compilation successful!\033[0m"

# Bonus compilation
bonus: CFLAGS += -Iincludes_bonus
bonus: $(OBJS_B) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_B) $(LIBFT) $(LDFLAGS)

# Generic rule for object files
# Mandatory objects
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus objects
%_bonus.o: %_bonus.c $(BONUS_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

# Libft
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# Clean object files
clean:
	@rm -f $(OBJS) $(OBJS_B)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "\033[0;33m🧹 Cleaned object files.\033[0m"

# Full clean
fclean: clean
	@rm -f $(NAME) $(BONUS_NAME) $(LIBNAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "\033[0;33m🧹 Fully cleaned project.\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re

# Emojis and ASCII art
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
