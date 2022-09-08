INC_DIR := include/
SRC_DIR	:= src/
OBJ_DIR	:= obj/
OBJ_DIRS = $(OBJ_DIR)


MINISHELL_PRE_SRCS = 	main cmd_utils env_init env_utils exit \
						parser_checks parser_utils parser pipe prompt quotes_remove \
						redirect_init redirect_parse sp_split signals tokens tokens_convert utils \
						executer builtins builtin_choose searchbinarypath checkexecutables \
						builtin_unset builtin_export assembleenv readline_minishell \
						readline_withoutspaces

MINISHELL_SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(MINISHELL_PRE_SRCS)))
MINISHELL_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(MINISHELL_PRE_SRCS)))

MINISHELL_NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra
INC	:= -I./$(INC_DIR) -I $(HOME)/.brew/opt/readline/include/
RM = rm -f

all:	$(MINISHELL_NAME)

$(MINISHELL_NAME): lib $(OBJ_DIRS) $(MINISHELL_OBJS) Makefile
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) -lncurses libft.a -L $(HOME)/.brew/opt/readline/lib/ -lreadline -o $(MINISHELL_NAME) 
	echo "----- \033[32m $@ compiled\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c include/minishell.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

lib:
	make -C libft
	make bonus -C libft
	echo "----- \033[32m libft compiled\033[0m  -----"
	cp libft/libft.a ./

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean
	rm -f /libs/libft.a

fclean: 	clean
	rm -f $(MINISHELL_NAME)
	rm -f libft.a
	make -C libft fclean
re:		fclean all
.PHONY : all clean fclean re
.SILENT :
