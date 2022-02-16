
SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/ft_atoi.c \
		srcs/time.c \
		srcs/philosopher.c \
		srcs/routine.c \
		srcs/death.c \

OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = inc/philo.h

CC = clang

CFLAGS = -Wall -Werror -Wextra -pthread -g3 -fsanitize=thread
RM = rm -f

.c.o:
	${CC} -c ${CFLAGS} -o $@ $< 

$(NAME):    ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	 fclean all

.PHONY: all clean fclean re
