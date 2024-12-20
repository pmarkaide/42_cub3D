# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbejar-s <dbejar-s@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 11:57:01 by dbejar-s          #+#    #+#              #
#    Updated: 2024/11/27 02:00:13 by dbejar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = \
	main.c \
	init.c \
	free.c \
	input.c \
	input_utils.c \
	input_parse.c \
	input_parse_fc.c \
	validation.c \
	validation_map.c \
	validation_map_utils.c \
	hooks.c \
	image_utils.c \
	player.c \
	player_utils.c \
	raycasting.c \
	floodfill.c \
	ray_utils.c \
	buffer_zone.c \
	textures.c

SRCS_DIR = src
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -o3 -g
LIBS = ./lib/MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
OBJS = $(SRCS:.c=.o)
RM = rm -f

INCLUDE = -I ./include/

LIBFT_DIR = lib/libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_INCLUDE = -I $(LIBFT_DIR)

TEST_SRCS = \
	test/map_tester.c

TEST_OBJS = $(TEST_SRCS:.c=.o)

# Exclude main.c from OBJS when compiling tests
OBJS_NO_MAIN = $(filter-out $(SRCS_DIR)/main.o, $(OBJS))

all: makelibft $(NAME)

makelibft:
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INCLUDE) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_INCLUDE) $(INCLUDE) $(LIBFT) -o $(NAME) $(LIBS)

test: $(TEST_OBJS) $(OBJS_NO_MAIN) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS_NO_MAIN) $(LIBFT_INCLUDE) $(INCLUDE) $(LIBFT) -o tester.o $(LIBS)
	
clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) $(TEST_OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all makelibft test clean fclean re