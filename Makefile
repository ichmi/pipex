# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/14 20:58:11 by frosa-ma          #+#    #+#              #
#    Updated: 2022/07/15 05:52:43 by frosa-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY	= all clean fclean re bonus

NAME	= pipex
CC		= clang
CFLAGS	= -Wall -Wextra -Werror
FT		= libft.a

SRCS	= main.c pipeline.c parser.c redirect.c error.c
OBJSDIR	= obj
OBJS	= $(addprefix ${OBJSDIR}/, ${SRCS:%.c=%.o})

all: ${NAME}

${NAME}: ${OBJSDIR} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} libft/${FT} -o $@

${OBJSDIR}:
	mkdir -p $@

${OBJS}: | ${FT}

${OBJSDIR}/%.o: src/%.c src/pipex.h
	${CC} ${CFLAGS} -c $< -o $@

${FT}: | libft
	@${MAKE} -C libft

libft:
	git clone https://github.com/ichmi/libft.git

clean:
	${MAKE} clean -C libft
	rm -rf ${OBJSDIR}

fclean: clean
	${MAKE} fclean -C libft
	rm -f ${NAME}

re: fclean all
