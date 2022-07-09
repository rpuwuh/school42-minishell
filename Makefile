INC_DIR := include/
SRC_DIR	:= src/
OBJ_DIR	:= obj/
OBJ_DIRS = $(OBJ_DIR)


MINISHELL_PRE_SRCS = 	main env_init env_utils exit prompt shell_init parser tokens
MINISHELL_SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(MINISHELL_PRE_SRCS)))
MINISHELL_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(MINISHELL_PRE_SRCS)))

MINISHELL_NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra
INC	:= -I./$(INC_DIR) -I $(HOME)/goinfre/.brew/opt/readline/include/
RM = rm -f

all:	$(MINISHELL_NAME)

$(MINISHELL_NAME): lib $(OBJ_DIRS) $(MINISHELL_OBJS)
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) -lncurses libft.a -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -o $(MINISHELL_NAME) 
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
