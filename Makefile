NAME = minishell

OBJDIR=./obj/

HEADER = minishell.h

SRC = executer.c builtin_pwd.c

SRC_O = $(addprefix $(OBJDIR),$(SRC:.c=.o))

LIBFT = $(addprefix $(OBJDIR),libft.a)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJDIR) $(LIBFT) $(OBJDIR)$(NAME).o $(SRC_O) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(LIBFT)  $(OBJDIR)$(NAME).o $(SRC_O) -o $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBFT): libft/*.c libft/*.h
	make -C ./libft/; cp ./libft/libft.a $(OBJDIR)libft.a; make fclean -C ./libft;

$(OBJDIR)$(NAME).o: $(NAME).c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.c $(NAME).c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME) $(NAME_CHECKER)

exec: all clean

clean: 
	rm -f $(LIBFT) $(GNL) $(SRC_O) $(SRC_BO) $(OBJDIR)$(NAME).o $(OBJDIR)$(NAME_CHECKER).o

fclean: clean
	rm -f $(NAME) $(NAME_CHECKER); rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re exec

	#-lreadline
	#-I /goinfre/bpoetess/.brew/Cellar/readline/8.1.2/include/readline/ -L\
	#/goinfre/bpoetess/.brew/Cellar/readline/8.1.2/lib/ -lreadline
