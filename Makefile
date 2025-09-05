NAME = 				cub3D
CC =				 cc
FLAGS = 			-Wall -Wextra -Werror -g
LDFLAGS = 			-L./Libft -lft

INC_DIR =			./includes
LIBFT_DIR =			./Libft
SRC_DIR = 			./src
INIT_DIR = 			$(SRC_DIR)/init
EVENTS_DIR =		$(SRC_DIR)/events
RAYCASTING_DIR =	$(SRC_DIR)/raycasting
TEX_DIR =			$(SRC_DIR)/textures
RENDER_DIR = 		$(SRC_DIR)/render
UTILS_DIR = 		$(SRC_DIR)/utils

INCLUDES =			-I${INC_DIR} -I./Libft/includes
LIBFT =				$(LIBFT_DIR)/libft.a

OBJS =				$(SRCS:.c=.o)

INC_FILES =			${INC_DIR}/cub3d.h $(INC_DIR)/parsing.h ${INC_DIR}/mlx.h ${INC_DIR}/includes.h ${INC_DIR}/events.h \
					${INC_DIR}/raycasting.h ${INC_DIR}/render.h ${INC_DIR}/utils.h

INIT =				$(INIT_DIR)/init.c
EVENTS =			$(EVENTS_DIR)/events.c $(EVENTS_DIR)/mouse.c $(EVENTS_DIR)/keys.c $(EVENTS_DIR)/move.c
RAYCASTING =		$(RAYCASTING_DIR)/raycaster.c $(RAYCASTING_DIR)/dda.c
TEX = 				$(TEX_DIR)/init.c $(TEX_DIR)/textures.c
RENDER = 			$(RENDER_DIR)/render.c $(RENDER_DIR)/minimap.c
UTILS = 			$(UTILS_DIR)/cleanup.c $(UTILS_DIR)/utils.c

SRCS =				$(SRC_DIR)/main.c $(INIT) $(EVENTS) $(RAYCASTING) $(TEX) $(RENDER) $(UTILS) \
					$(SRC_DIR)/parsing/parsing.c \
					$(SRC_DIR)/parsing/parsing2.c $(SRC_DIR)/parsing/parsing3.c $(SRC_DIR)/parsing/parsing4.c $(SRC_DIR)/parsing/parsing_command.c \
					$(SRC_DIR)/parsing/parsing_command2.c $(SRC_DIR)/parsing/parsing_command3.c $(SRC_DIR)/parsing/parsing_command4.c \
					$(SRC_DIR)/parsing/parsing_command5.c

all:				$(LIBFT) $(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LDFLAGS)

%.o: %.c			$(INC_FILES)
						$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

$(LIBFT):
					make -C $(LIBFT_DIR)

clean:
					make clean -C $(LIBFT_DIR)
					rm -f $(OBJS)

fclean:				clean
						make fclean -C $(LIBFT_DIR)
						rm -f $(NAME)

re:					fclean all

vg:
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/m.cub

.PHONY:				all clean fclean re
