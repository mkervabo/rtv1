# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 11:46:19 by mkervabo          #+#    #+#              #
#    Updated: 2019/04/30 13:57:59 by mkervabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
CFLAGS = -Wall -Wextra -I ./include -g $(shell pkg-config --cflags SDL2) #-fsanitize=address

OBJS = build/main.o build/object.o build/vec3.o build/light.o build/scene.o build/camera.o build/color.o build/rotate.o

all: $(NAME)

build/%.o: src/%.c include/rtv1.h Makefile
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(shell pkg-config --libs SDL2) $(OBJS) -o $(NAME)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
