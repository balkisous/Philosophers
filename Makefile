# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 23:02:52 by ddecourt          #+#    #+#              #
#    Updated: 2022/02/15 16:03:19 by bben-yaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/ft_atoi.c \
		srcs/time.c \
		srcs/philosopher.c \
		#srcs/philo_utils.c \
		#srcs/routine.c \
		#srcs/check_dead.c \

OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = inc/philo.h

CC = clang

CFLAGS = -Wall -Werror -Wextra -pthread
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
