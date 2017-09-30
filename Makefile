# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/29 20:04:31 by jdaufin           #+#    #+#              #
#    Updated: 2017/09/30 21:34:32 by jdaufin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

NAME = lem_in

TEST_DIR = tests/
SRC_DIR = srcs/
SRC_RDX = ft_antlist ft_error ft_options get_input store_input
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_RDX)))
HDR_DIR = includes/
FT_DIR = libft/
PRINTF_DIR = ft_printf/

all : $(NAME)

clean :

fclean : clean

re : fclean all
