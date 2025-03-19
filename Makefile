# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 09:45:00 by fmixtur           #+#    #+#              #
#    Updated: 2025/03/19 09:48:39 by fmixtur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
SANITIZE    = -fsanitize=address -g3
RM          = rm -f

SRCS        = main.c \
              actions.c \
              monitor.c \
              set.c \
              utils.c \
              cleanup.c

OBJS        = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread

all: $(NAME)

sanitize: CFLAGS += $(SANITIZE)
sanitize: re
	@echo "Compiled with sanitize flags"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re sanitize 