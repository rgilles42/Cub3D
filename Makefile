# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 19:04:10 by rgilles           #+#    #+#              #
#    Updated: 2020/07/05 19:04:12 by rgilles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

UNAME	= ${shell uname}
ifeq (${UNAME}, Darwin)
	MLX 	= minilibx-metal/
	LINKFL 	= -framework OpenGL -framework AppKit -fsanitize=address
	MLX_NAME = libmlx.dylib
else
	MLX		= minilibx-linux/
	LINKFL	= -lXext -lX11 -lm
	MLX_NAME = libmlx.a
endif

SRCSF	= main.c parse_file.c mlx_extras.c deal_map.c build_image.c \
		raycasting.c create_bmp.c sprite_management.c check_error.c

SRCSD	= srcs/
INCL	= includes/
LIBFT	= Libft/

SRCS	=	$(addprefix ${SRCSD},${SRCSF})
OBJS	=	${SRCS:.c=.o}


.c.o :		${INCL}cub3d.h ${LIBFT}${INCL}libft.h
			${CC} ${CFLAGS} -I${LIBFT}${INCL} -I${MLX} -I${INCL} -c $< -o ${<:.c=.o}


${NAME} :	${OBJS}
			make -C ${LIBFT}
			cp ${LIBFT}libft.a ./
			make -C ${MLX}
			cp ${MLX}${MLX_NAME} ./
			${CC} -o ${NAME} ${OBJS} libft.a ${MLX_NAME} ${LINKFL}


all :		${NAME}

clean :
			find . -type f -name "*.o" -delete

fclean :	clean
			find . -type f -name "*.a" -delete
			rm -rf ${NAME}

re :		fclean all

.PHONY :	re clean fclean
