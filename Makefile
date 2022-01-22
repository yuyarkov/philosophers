# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 20:08:26 by dirony            #+#    #+#              #
#    Updated: 2022/01/22 15:54:17 by dirony           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_B = philo_bonus

HEADER = philo.h

HEADER_B = bonus/philo_bonus.h 

SRC = 		main.c							number_utils.c\
			utils.c							parse_utils.c\
			life_cycle_utils.c
			
SRC_BONUS = bonus/main_bonus.c					bonus/list_utils_bonus.c\
										
OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

COMPILE = gcc $(CFLAGS)

REMOVE = rm -f

%.o 	:	%.c	$(HEADER)
			$(COMPILE) -c $< -o $@

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(COMPILE) $(OBJ) -o $(NAME)

bonus:
	@make NAME="$(NAME_B)" OBJ="$(OBJ_BONUS)" HEADER="$(HEADER_B)" all

clean:
	@$(REMOVE) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(REMOVE) $(NAME) $(NAME_B)

re: fclean all
