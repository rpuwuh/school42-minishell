NAME = minishell

OBJDIR=./obj/

HEADER = minishell.h

SRC =

SRC_O = $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

$(NAME): $(OBJDIR) $(OBJDIR)$(NAME).o $(SRC_O) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(OBJDIR)$(NAME).o $(SRC_O) -lreadline -o $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)$(NAME).o: $(NAME).c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.c $(NAME).c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

exec: all clean

clean: 
	rm -f $(SRC_O) $(OBJDIR)$(NAME).o;  rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re exec
