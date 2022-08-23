# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 14:24:40 by nheo              #+#    #+#              #
#    Updated: 2022/08/23 14:55:23 by heonamjun        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRCS = philo_bonus.c \
		ft_atoi_bonus.c \
		init_bonus.c \
		process_bonus.c \
		util1_bonus.c \
		util2_bonus.c

HDRS = ./includes

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g

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

.PHONY : clean fclean re all
