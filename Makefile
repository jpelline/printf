# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 17:25:40 by jpelline          #+#    #+#              #
#    Updated: 2025/05/13 19:03:12 by jpelline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= ft_printf.c	
OBJS		= $(SRCS:.c=.o)
EXEC_SRCS	= $(SRCS) main.c
EXEC_OBJS	= $(EXEC_SRCS:.c=.o)

NAME		= libftprintf.a
LIBS		= -L$(LIBFT_DIR)
INC			= -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(OBJS)
	@echo "Archiving $@"
	@cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "Cleaning object files.."
	rm -f $(OBJS) $(EXEC_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	@echo "Cleaning executable/archive.."
	rm -f $(NAME) custom_exec
	$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

exec: custom_exec

custom_exec: $(NAME) main.o
	@echo "Building custom executable: $@"
	$(CC) $(CFLAGS) main.o -L. -lftprintf -o $@

.PHONY: all clean fclean re exec custom_exec
