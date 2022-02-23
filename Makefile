# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asippy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 19:25:19 by asippy            #+#    #+#              #
#    Updated: 2022/02/23 19:30:32 by asippy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	fdf

#COLORS
BOLD				= 	\033[1m
RED					= 	\033[31m
GREEN				= 	\033[32m
RESET				= 	\033[0m

#SOURCES
SRCS_DIR			= 	source/
SRCS_LIST			= 	fdf.c general_utils.c\
						map.c map_utils.c\
						get_next_line.c get_next_line_utils.c\
						split.c\
						global_gradient.c\
						mlx.c\
						conf.c\
						coordinates.c\
						draw.c draw_color_utils.c draw_math_utils.c
SRCS_DIR_BONUS		= 	source_bonus/
SRCS_LIST_BONUS		= 	fdf_bonus.c general_utils_bonus.c\
						map_bonus.c map_utils_bonus.c\
						get_next_line_bonus.c get_next_line_utils_bonus.c\
						split_bonus.c\
						global_gradient_bonus.c\
						mlx_bonus.c\
						conf_bonus.c\
						coordinates_bonus.c\
						draw_bonus.c draw_color_utils_bonus.c draw_math_utils_bonus.c


#LIBS TO LINK WITH
LIB_MINI			= 	-lmlx -framework OpenGL -framework AppKit
LIB_MATH			= 	-lm

#HEADER
HEAD_DIR			= 	include/
HEAD_NAME			=	fdf.h
HEAD_DIR_BONUS		=	include_bonus/
HEAD_NAME_BONUS		=	fdf_bonus.h
HEAD				= 	$(HEAD_DIR)$(HEAD_NAME)

#HEADERS TO COMPILE WITH
INC					= 	-I$(HEAD_DIR) -Imlx -Im

#OBJECTS
OBJS_DIR			= 	object/
OBJS_DIR_BONUS		=	object_bonus/
OBJS_LIST			= 	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS				= 	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

#COMPILER
CC					= 	gcc
CFLAGS				= 	-Wall -Werror -Wextra
OFLAGS				= 	-O2

RM					= 	rm -rf

$(NAME):				$(OBJS_DIR) $(OBJS)
						@echo "$(GREEN)Creating $(NAME)...$(RESET)"
						$(CC) $(OBJS) $(LIB_MINI) $(LIB_MATH) -o $(NAME)
						@echo "$(GREEN)$(BOLD)$(NAME) was created!$(RESET)"

all:					$(NAME)

$(OBJS_DIR)%.o:			$(SRCS_DIR)%.c $(HEAD)
						$(CC) $(OFLAGS) $(CFLAGS) $(INC) -c $< -o $@
						@echo "$(GREEN)OK!$(RESET)"

$(OBJS_DIR):
						@echo "$(GREEN)Creating $(OBJS_DIR)...$(RESET)"
						mkdir $(OBJS_DIR)
						@echo "$(GREEN)$(BOLD)$(OBJS_DIR) was created!$(RESET)"

bonus:
						@make SRCS_DIR="$(SRCS_DIR_BONUS)" SRCS_LIST="$(SRCS_LIST_BONUS)" HEAD_DIR="$(HEAD_DIR_BONUS)" HEAD_NAME="$(HEAD_NAME_BONUS)" OBJS_DIR="$(OBJS_DIR_BONUS)" 

clean:
						@echo "$(RED)Deleting the objects...$(RESET)"
						$(RM) $(OBJS_DIR) $(OBJS_DIR_BONUS)
						@echo "$(RED)$(BOLD)The objects were deleted!$(RESET)"

fclean:					clean
						@echo "$(RED)Deleting $(NAME)...!$(RESET)"
						$(RM) $(NAME)
						@echo "$(RED)$(BOLD)$(NAME) was deleted!$(RESET)"

re:						fclean all

.PHONY:					all bonus clean fclean re