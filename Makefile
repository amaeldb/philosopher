SRCS =	philo.c init.c utils.c

OBJS =	${SRCS:.c=.o}

FLAGS =	-Wall -Wextra -Werror

NAME =	philo

%.o: 	%.c
	@ gcc ${FLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
	@ gcc ${FLAGS} ${OBJS} -lpthread -o ${NAME}

clean:		${OBJS}
	@ rm -rf ${OBJS} ${DEPS}

fclean:		clean
	@ rm -rf ${NAME}

re:			fclean
	@ make all