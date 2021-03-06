# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdaufin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/29 20:04:31 by jdaufin           #+#    #+#              #
#    Updated: 2017/11/01 20:30:17 by jdaufin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

NAME = lem-in
TEST = t_input

TEST_DIR = tests/
TEST_SRC = $(addprefix $(TEST_DIR), $(addsuffix .c, $(TEST)))
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

RDX = get_input store_input ft_options ft_error ft_parse_input ft_parse_room\
	  ft_parse_tube ft_parse_comment ft_antlist status_flag analyse_comments\
	  add_room ft_roomlist add_tube tubes_initloop check_ends init_weights\
	  set_weights ft_lstdup get_weight ft_pathlist get_path get_start solver\
	  ft_itinerary move_ants move_all
SRC_DIR = srcs/
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(RDX)))
OBJ_DIR = builts/
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(RDX)))

MAIN = exec_lem_in
MAIN_SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(MAIN)))
MAIN_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(MAIN)))

HDR_DIR = includes/
FT_DIR = libft/
FT_HDR = $(addprefix $(FT_DIR), includes/)
PRINTF_DIR = ft_printf/
PRINTF_HDR = $(addprefix $(PRINTF_DIR), includes/)

all : $(NAME) $(TEST)

$(TEST) : $(OBJ) $(TEST_OBJ) 
	make -C $(FT_DIR)
	make -C $(PRINTF_DIR)
	$(CC) $(FLAGS) $^ -I $(HDR_DIR) -I $(FT_HDR) -I $(PRINTF_HDR)\
		-L $(FT_DIR) -lft -L $(PRINTF_DIR) -lftprintf -o $@

$(NAME) : $(OBJ) $(MAIN_OBJ)
	make -C $(FT_DIR)
	make -C $(PRINTF_DIR)
	$(CC) $(FLAGS) $^ -I $(HDR_DIR) -I $(FT_HDR) -I $(PRINTF_HDR)\
		-L $(FT_DIR) -lft -L $(PRINTF_DIR) -lftprintf -o $@

$(TEST_DIR)%.o : $(TEST_DIR)%.c
	$(CC) $(FLAGS) -c $< -I $(HDR_DIR) -I $(FT_HDR) -I $(PRINTF_HDR) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir $(OBJ_DIR) 2> /dev/null || true
	$(CC) $(FLAGS) -c $< -I $(HDR_DIR) -I $(FT_HDR) -I $(PRINTF_HDR) -o $@

clean :
	make -C $(FT_DIR) clean
	make -C $(PRINTF_DIR) clean
	rm $(TEST_OBJ)
	rm -r $(OBJ_DIR)

fclean : clean
	make -C $(FT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	rm $(TEST)
	#rm $(NAME)

re : fclean all
