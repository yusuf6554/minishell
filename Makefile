NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LDFLAGS = -lreadline

SRC_FILES = main.c utils/shell_core.c utils/shell_input.c \
			utils/utils_env_mgmt.c utils/utils_env.c \
			utils/utils_error.c utils/utils_free.c \
			utils/utils_memory.c

SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
OBJ_DIR = obj

DIRS := $(sort $(dir $(OBJS)))

INC_DIR = include
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