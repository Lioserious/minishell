################################################################################
#################### PROJECT CONFIGURATION #####################################
################################################################################
# Compilers and flags
CC = cc
CC_FLAGS = -Wall -Werror -Wextra
RM = rm -rf
# Targets
NAME = minishell
################################################################################
#################### DIRECTORIES ##############################################
################################################################################
OBJ_DIR = _obj
SRC_DIR = src
INC_DIR = includes
LIBFT_DIR = libft
################################################################################
#################### SOURCE FILES #############################################
################################################################################
# Main source files
SRC_FILES = main.c
# Parser source files (in src/parser/)
SRC_PARSER = cmd_list.c file_to_list.c parser_helper.c parser.c parser_test.c
# Executor source files (in src/executor/)
SRC_EXECUTOR = exec.c external_exec.c redirections.c exec_help.c
# Builtins source files (in src/builtins)
SRC_BUILTINS = execute_builtins.c pwd.c echo.c cd.c env.c env_help.c export.c unset.c exit.c
# Error handler source files (in src/error/)
SRC_ERROR = error_handler.c clean_exit.c
# Garbage collector source files (in src/garbage_collector/)
SRC_GC = garbage_collector_add.c garbage_collector_empty.c garbage_collector_print.c \
         gc_holder.c gc_malloc.c gc_readline.c gc_strdub.c gc_substr.c gc_split.c gc_strjoin.c
# Tokenizer source files (in src/tokenizer)
SRC_TOK = tokenizer.c handle_env_variable.c handle_quotes.c handle_special_char.c \
         handle_word.c tokenizer__utils.c tokenizer_utils.c handle_eof.c tokenizer_test.c
# Signals source files (in src/signals)
SRC_SIGNALS = signals.c terminal.c
# All source files
SRC = $(SRC_FILES) \
      $(addprefix parser/, $(SRC_PARSER)) \
      $(addprefix error/, $(SRC_ERROR)) \
      $(addprefix garbage_collector/, $(SRC_GC)) \
      $(addprefix executor/, $(SRC_EXECUTOR)) \
      $(addprefix builtins/, $(SRC_BUILTINS)) \
      $(addprefix tokenizer/, $(SRC_TOK)) \
	  $(addprefix signals/, $(SRC_SIGNALS))
################################################################################
#################### OBJECT FILES ############################################
################################################################################
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
################################################################################
#################### COMPILATION FLAGS ######################################
################################################################################
CFLAGS := $(CC_FLAGS) -g -MMD -MP -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS := -L$(LIBFT_DIR) -lft -lreadline
# OS-specific configuration
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin) # macOS
 LDFLAGS += -L/usr/local/opt/readline/lib
 CFLAGS += -I/usr/local/opt/readline/include
else ifeq ($(UNAME), Linux) # Linux
 LDFLAGS += -lncurses
endif
################################################################################
#################### RULES ###################################################
################################################################################
# Default target
all: $(NAME)
# Create object directory and subdirectories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/executer
	@mkdir -p $(OBJ_DIR)/error
	@mkdir -p $(OBJ_DIR)/garbage_collector
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/tokenizer

# Compile libft
libft:
	@echo "\033[0;34mCompiling libft...\033[0m"
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "\033[0;32mLibft compiled successfully\033[0m"
# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "\033[0;32mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
# Rule to create the executable
$(NAME): libft $(OBJ)
	@echo "\033[0;32mCompiling $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "\033[0;32mSuccessful Compilation of $(NAME)\033[0m"
# Clean up object files
clean:
	@echo "\033[0;32mCleaning object files...\033[0m"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[0;32mCleaned object files successfully\033[0m"
# Clean up all generated files
fclean: clean
	@echo "\033[0;32mRemoving executable...\033[0m"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[0;32mRemoved files successfully\033[0m"
# Rebuild project
re: fclean all
# Debug with Valgrind
debug: CFLAGS += -g
debug: re sub.sub
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=sub.sub ./$(NAME)
# Address Sanitizer build
san: CFLAGS += -fsanitize=address -g
san: LDFLAGS += -fsanitize=address
san: re
# Include dependency files
-include $(OBJ:.o=.d)
.PHONY: all clean fclean re debug san libft
