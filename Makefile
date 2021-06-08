# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmendes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 16:37:43 by jmendes           #+#    #+#              #
#    Updated: 2021/05/28 00:33:04 by jmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
FLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = libftprintf.a
INCLUDE = ft_printf.h 

SRC = flags.c\
			ft_printf.c\
			ft_strdup.c\
			printers.c\
			printd.c\
			printd0.c\
			printd1.c\
			printc.c\
			printu.c\
			printx.c\
			convert.c\
			
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	ar -rcs	$(NAME) $(OBJS)
	ranlib $(NAME)

.c.o: $(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
