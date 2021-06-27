# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmendes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 16:37:43 by jmendes           #+#    #+#              #
#    Updated: 2021/06/27 17:30:11 by jmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
FLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = libftprintf.a
INCLUDE = ft_printf.h 

SRC = flags.c\
	  		width_precision.c\
			ft_strdup.c\
			ft_printf.c\
			printers.c\
			printd_pos.c\
			printd_zero.c\
			printd_neg.c\
			printd_neg1.c\
			printc.c\
			prints.c\
			printu.c\
			printu1.c\
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
