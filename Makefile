# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zgargasc <zgargasc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/16 16:06:55 by zgargasc       #+#    #+#                 #
#    Updated: 2020/01/15 11:14:41 by zgargasc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = printf.c convs.c convs2.c getflags.c padding.c asciiconvs.c

INC = printf.h

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

bonus: $(NAME)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
