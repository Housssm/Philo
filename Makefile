SRCS = \
	main.c \
	parsing.c \
	parsing_utils.c 

OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = philo.h

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -pthread

all:     ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}


%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

clean:    
	rm -f ${OBJS}

fclean:    clean;
	rm -f ${NAME}
	rm -f a.out

re:    fclean all

.PHONY: all clean fclean re
