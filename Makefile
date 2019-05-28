# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 11:46:19 by mkervabo          #+#    #+#              #
#    Updated: 2019/05/28 15:11:40 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = gcc
CFLAGS = -Wall -Wextra -I./include -I./libtoml/include $(shell pkg-config --cflags sdl2) -flto -O2 #-fsanitize=address

include src.mk

OBJS=$(patsubst src/%.c,build/%.o,$(SRCS))

all: $(NAME)

build/%.o: src/%.c include/rtv1.h Makefile
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C libtoml libtoml.a
	$(CC) $(CFLAGS) $(shell pkg-config --libs sdl2) -lm $(OBJS) libtoml/libtoml.a -o $(NAME)

clean:
	$(MAKE) -C libtoml clean
	rm -rf build

fclean: clean
	$(MAKE) -C libtoml fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
