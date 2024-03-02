# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scambier <scambier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 20:09:27 by scambier          #+#    #+#              #
#    Updated: 2024/03/02 17:31:00 by scambier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===CONFIGURATION===
NAME = pipex
NAME_BONUS = pipex_bonus

SRC =\
	mandatory/main.c\
	mandatory/str_exec.c

SRC_BONUS =\
	bonus/main.c\
	bonus/str_exec.c

CFLAGS = -Wall -Werror -Wextra

LIBS = \
	libft/libft.a\

INCLUDES = -Ilibft/

OBJ_DIR = obj

#===AUTOMATIC VARS===

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(addsuffix _bonus.o, $(notdir $(basename $(SRC_BONUS)))))

LIB_FLAGS = $(addprefix -L, $(dir $(LIBS))) $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIBS))))

#===TARGETS===
all : $(NAME)

bonus : $(NAME_BONUS)

#===COMPILING===
$(OBJ_DIR) :
	$(shell mkdir -p $(OBJ_DIR))
$(OBJ_DIR)/%.o : mandatory/%.c
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
$(OBJ_DIR)/%_bonus.o : bonus/%.c
	cc $(CFLAGS) -o $@ -c $< $(INCLUDES)
%.a :
	make -C $(dir $@)

#===LINKING===
$(NAME_BONUS) : $(OBJ_DIR) $(LIBS) $(OBJ_BONUS)
	cc -o $(NAME_BONUS) $(OBJ_BONUS) $(LIB_FLAGS)
$(NAME) : $(OBJ_DIR) $(LIBS) $(OBJ)
	cc -o $(NAME) $(OBJ) $(LIB_FLAGS)

#===CLEAN===
clean :
	rm -rf $(OBJ_DIR) || true

#===FCLEAN===
fclean : clean
	rm -f $(NAME) $(NAME_BONUS) || true

#===RE===
re : fclean all


.PHONY : re fclean clean all default bonus