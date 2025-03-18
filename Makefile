# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 17:17:16 by marcnava          #+#    #+#              #
#    Updated: 2025/03/17 02:21:35 by marcnava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
LIBFT = ./libs/libft

CC = gcc
# CFLAGS = -Wall -Wextra -Werror

SRC_CLIENT = ./src/client.c
SRC_SERVER = ./src/server.c

OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
OBJS_SERVER = $(SRC_SERVER:.c=.o)

all: $(LIBFT)/libft.a $(CLIENT) $(SERVER)

$(LIBFT)/libft.a:
	@$(MAKE) --no-print-directory -s -C $(LIBFT)

$(CLIENT): $(OBJS_CLIENT) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) -L$(LIBFT) -lft

$(SERVER): $(OBJS_SERVER) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) -L$(LIBFT) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
