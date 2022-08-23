# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 14:24:40 by nheo              #+#    #+#              #
#    Updated: 2022/08/23 14:46:28 by heonamjun        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = philo.c \
		ft_atoi.c \
		init.c \
		process.c \
		util1.c \
		util2.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

all : $(NAME)

%.o : %.c
	cc $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : clean fclean re all
