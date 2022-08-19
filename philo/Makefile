# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 14:24:40 by nheo              #+#    #+#              #
#    Updated: 2022/08/19 14:48:01 by nheo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c \
		ft_atoi.c \
		init.c \
		process.c \
		util1.c \
		util2.c

HDRS = ./includes

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

all : $(NAME)

%.o : %.c
	cc $(CFLAGS) -c -o $@ $< -I $(HDRS)

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : clean fclean re all bonus