# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/17 13:38:49 by vbuonvin          #+#    #+#              #
#    Updated: 2021/07/01 17:07:55 by rboldini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_printf_fd.a

PRINTF_SRCS = 	ft_printf.c							\
				ft_printf_utils.c 					\
				controllo.c 						\
				ft_printf_setup_utils.c				\
				ft_printf_setups.c 					\
				ft_unsigned_itoa.c					\
				handle_negative.c					\
				process_char.c						\
				process_percentage.c				\
				process_pointer.c					\
				process_signed_decimal_utils.c		\
				process_signed_decimal.c			\
				process_string.c					\
				process_unsigned_decimal.c			\
				process_unsigned_hex.c				\
				ft_setup_precision.c

PRINTF_DIR = 	.

LIBFT_DIR = 	../libft

PRINTF_DIRSRCS = $(addprefix ${PRINTF_DIR}/, ${PRINTF_SRCS})

OBJS	= ${PRINTF_DIRSRCS:.c=.o}

%.o: %.c
			gcc -Wall -Wextra -Werror -o $@ -c $< 

all: $(NAME)

$(NAME):  ${OBJS}
			ar -rc $(NAME) $(OBJS) ../libft/libft.a

clean:
			rm -f $(OBJS)

fclean: clean
			rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
