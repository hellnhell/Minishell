# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/20 18:30:24 by hellnhell         #+#    #+#              #
#    Updated: 2020/11/04 19:21:14 by isfernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	minishell

SRCS	=   src/main.c              \
			src/read_path.c			\
			src/split_line.c		\
			src/echo.c				\
			src/pwd.c				\
			src/cd.c				\
			src/export.c			\
			src/unset.c				\
			src/env.c				\
			src/exit.c				\
			src/ft_strjoin_sl.c		\
			src/check_our_implement.c	\
			src/split_dc.c 				\
			src/list_add_elements.c	\
			src/list_pop_elements.c \
			src/list_utils.c		\
			src/create_elements.c	\
			src/utils.c
 
GCC			=   @gcc -Wall -Wextra -Werror -g3
OBJS		=   $(SRCS:.c=.o)
LIBFT		= 	libft/libft.a
INCLUDES	=   ./

all: 		$(NAME)
$(NAME):	$(OBJS)
		@$(MAKE) -C libft
		@$(GCC) -I$(INCLUDES) $(LIBFT) $(OBJS) -o $(NAME)
clean:
			-@$(RM) $(OBJS)
			@$(MAKE) -C libft clean
fclean:		clean
			-@$(RM) $(NAME) $(LIBFT)
re:			fclean all
.PHONY:		all clean fclean re bonus
