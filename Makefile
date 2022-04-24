NAME		=	pipex

D_UTILES	=	utiles/
SRCS		=	pipex.c \
				$(D_UTILES)exit_perror.c \
				$(D_UTILES)ft_split.c \
				$(D_UTILES)ft_strdup.c \
				$(D_UTILES)ft_strjoin.c \
				$(D_UTILES)ft_strlcpy.c \
				$(D_UTILES)ft_strlen.c \
				$(D_UTILES)ft_strncmp.c \
			
OBJS		= $(SRCS:%.c=%.o)

LIBC		= ar rc

FLAGS		= -Wall -Wextra -Werror

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		gcc -o $(NAME) $(OBJS)

%.o			:	%.c
		gcc $(FLAGS) -c $^ -I./ -o $@

clean		:
		rm -f $(OBJS)
		
fclean		:	clean
		rm -f $(NAME)
		
re			:	fclean all

.PHONY		:	all clean fclean re bonus
