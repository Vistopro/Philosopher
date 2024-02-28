# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 17:36:49 by vicrodri          #+#    #+#              #
#    Updated: 2024/02/14 18:59:23 by vicrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC	=	gcc -g -pthread

CFLAGS	=	-Wall -Wextra -Werror


SOURCES	=	$(wildcard src/*.c)	

OBJECTS	=	$(SOURCES:.c=.o)

%.o: %.c
	@$(CC)$(FLAGS) -c $< -o $@

all: $(NAME)


$(NAME)		: $(OBJECTS) 
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
			@echo "$(GREEN)$(NAME) -> program created! $(DEFAULT)"

clean:
	@rm -f $(OBJECTS)
		@echo "$(YELLOW)$(NAME) -> objects deleted! $(DEFAULT)"

fclean:	clean
	@rm -f $(NAME)
		@echo "$(RED)$(NAME) -> program deleted! $(DEFAULT)"

re:	fclean all

.PHONY:	all clean fclean re 

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m