SRCS		=	./image_funs.c \
			./fractol.c \
			./ft_atof.c \
			./ft_atoi.c

OBJS		=	${SRCS:.c=.o}

NAME		=	fractol

CFLAGS		=	-Wall -Wextra -Werror -g3
MLXFLAGS	=	-framework OpenGL -framework AppKit

.c.o:
			cc ${CFLAGS} -c $< -o ${<:.c=.o}


${NAME}:	${OBJS}
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) -lmlx $(OBJS)
		

${OBJS}:	fractol.h

.PHONY:		clean fclean all re bonus

all:		${NAME}

clean:
		rm -f ${OBJS}


fclean:		clean
		rm -f ${NAME}

re:		fclean all

bonus: 		all