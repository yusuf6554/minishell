NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LDFLAGS = -lreadline

MAIN_SRC = main.c

SRC_FILES = utils/shell_core.c utils/shell_input.c \
			utils/utils_env_mgmt.c utils/utils_env.c \
			utils/utils_error.c utils/utils_free.c \
			utils/utils_memory.c \
			parsing/tokenizer.c parsing/tokenizer_expand.c \
			parsing/command.c parsing/pipeline.c parsing/signal.c \
			execution/executor.c execution/pipes.c \
			execution/redirections.c execution/builtin_dispatcher.c \
			execution/external_command.c execution/builtin_checker.c \
			execution/pipeline_utils.c execution/heredoc.c \
			execution/builtins/builtin_echo.c execution/builtins/builtin_cd.c \
			execution/builtins/builtin_pwd.c execution/builtins/builtin_export.c \
			execution/builtins/builtin_unset.c execution/builtins/builtin_env.c \
			execution/builtins/builtin_exit.c

SRCS_DIR = src
SRCS = $(MAIN_SRC) $(addprefix $(SRCS_DIR)/, $(SRC_FILES))

MAIN_OBJ = $(MAIN_SRC:.c=.o)
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(MAIN_OBJ) $(OBJ_FILES))
OBJ_DIR = obj

DIRS := $(sort $(dir $(OBJS)))

INC_DIR = includes
INC = -I$(INC_DIR)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully$(RESET)"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(DIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(BLUE)  → Compiled: $< $(RESET)"

$(OBJ_DIR)/%.o: %.c | $(DIRS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(BLUE)  → Compiled: $< $(RESET)"

$(DIRS):
	@mkdir -p $@
	@echo "$(YELLOW)  → Folder created: $@$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ Libft compiled successfully$(RESET)"

clean:
	$(RM) -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) fclean
	@echo "$(RED)✗ Object files in ($(OBJ_DIR)) successfully cleaned$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)✗ Program ($(NAME)) successfully cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re