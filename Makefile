# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scambier <scambier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 20:09:27 by scambier          #+#    #+#              #
#    Updated: 2024/02/28 19:13:14 by scambier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

$(NAME) : main.c str_exec.c
	cc -o $(NAME) main.c str_exec.c -Ilibft/ -Llibft/ -lft -g3

all : $(NAME)
fclean :
clean :
re :