# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 20:08:26 by dirony            #+#    #+#              #
#    Updated: 2022/01/29 15:00:50 by dirony           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_B = philo_bonus

HEADER = src/philo/philo.h

HEADER_B = src/philo_bonus/philo_bonus.h 

SRC = 		src/philo/main.c					src/philo/life_cycle_utils.c\
			src/philo/utils.c					src/philo/parse_utils.c
			
SRC_BONUS = src/philo_bonus/main_bonus.c		src/philo_bonus/life_cycle_utils_bonus.c\
			src/philo_bonus/utils_bonus.c		src/philo_bonus/parse_utils_bonus.c
										
OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g

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
