# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/14 20:58:11 by frosa-ma          #+#    #+#              #
#    Updated: 2022/07/20 20:57:38 by frosa-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY	= all clean fclean re bonus

NAME	= pipex
CC		= clang
CFLAGS	= -Wall -Wextra -Werror
FT		= libft.a

SRCS	= main.c pipeline.c parser.c exec.c error.c
B_SRCS	= main_bonus.c pipeline_bonus.c parser_bonus.c exec_bonus.c
B_SRCS	+= error_bonus.c heredoc_bonus.c gnl_bonus.c
OBJSDIR	= obj
OBJS	= $(addprefix ${OBJSDIR}/, ${SRCS:%.c=%.o})
B_OBJS	= $(addprefix ${OBJSDIR}/, ${B_SRCS:%.c=%.o})

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

bonus: ${NAME}_bonus

${NAME}_bonus: ${OBJSDIR} ${B_OBJS}
	${CC} ${CFLAGS} ${B_OBJS} libft/${FT} -o $@

${B_OBJS}: | ${FT}

${OBJSDIR}/%.o: bonus/%.c bonus/pipex_bonus.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${MAKE} clean -C libft
	rm -rf ${OBJSDIR}

fclean: clean
	${MAKE} fclean -C libft
	rm -f ${NAME} ${NAME}_bonus

re: fclean all
