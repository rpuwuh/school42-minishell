NAME			= libft.a

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

SRCS			=	ft_atoi.c  ft_itoa.c \
					ft_bzero.c  ft_memchr.c  ft_memcmp.c \
					ft_memcpy.c  ft_memmove.c  ft_memset.c \
					ft_calloc.c  ft_strdup.c \
					ft_isalnum.c  ft_isalpha.c  ft_isascii.c  ft_isdigit.c  ft_isprint.c \
					ft_putchar_fd.c  ft_putendl_fd.c  ft_putnbr_fd.c  ft_putstr_fd.c \
					ft_split.c \
					ft_strchr.c  ft_striteri.c  ft_strjoin.c \
					ft_strlcat.c  ft_strlcpy.c  ft_strlen.c  ft_strmapi.c \
					ft_strncmp.c ft_strnstr.c  ft_strrchr.c  ft_strtrim.c  ft_substr.c   \
					ft_toupper.c ft_tolower.c ft_strcmp.c

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJS		= $(BONUS:.c=.o)

HEADERS			= libft.h

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(UP)$(CUT)
	@echo $(Y)Compiling [$<]...$(X)

all: $(NAME)

$(NAME): $(OBJS)
	@printf $(UP)$(CUT)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@ar -rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)
	@echo

clean:
	@rm -f $(OBJS)
	@echo $(R)Removed libft .o$(X)

fclean: clean
	@rm -f $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

bonus:			$(OBJS) $(BONUS_OBJS) $(HEADERS)
				@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
				@touch bonus

re:				fclean all


.PHONY:			all clean fclean re
