NAME = cub3D

CC = gcc -g

FLAGS = -Wall -Werror -Wextra 

FRAMEWORKS = -framework OpenGL -framework Appkit

INCLUDES = -I includes/ -I res/libft/

GNL_DIR =		res/gnl/

GNL_LIST =		get_next_line.c \
				get_next_line_utils.c \

LIBFT =			res/libft/

SRC_DIR =		src/

SRC_LIST =		cub3d.c \
				key_event.c \
				utils.c \
				screenshot.c \
				pixel_utils.c

INIT_DIR =		init/

INIT_LIST =		init.c \
				init_utils.c

PARSE_DIR =		parsing/

PARSE_LIST =	parse.c \
				get_r_tex_map.c \
				parsing_utils.c \
				check_map.c \
				get_map.c \
				get_floor_ceiling_sprite.c \

RENDER_DIR =	render/
 
RENDER_LIST =	render_player.c \
				render_utils.c \
				render_sprite.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

GNL = $(addprefix $(GNL_DIR), $(GNL_LIST))

INIT = $(addprefix $(INIT_DIR), $(INIT_LIST))

PARSE = $(addprefix $(PARSE_DIR), $(PARSE_LIST))

RENDER= $(addprefix $(RENDER_DIR), $(RENDER_LIST))

SRCS = $(SRC) $(GNL) $(INIT) $(PARSE) $(RENDER)

OBJ = $(SRCS:.c=.o)

LIBRARY = -L. -lft -lmlx

.PHONY: all clean fclean re run

all: $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) libft
		make -C minilibx_opengl_20191021
		mv minilibx_opengl_20191021/libmlx.a .
		cp $(LIBFT)/libft.a .
		$(CC) $(FLAGS) $(INCLUDES) $(LIBRARY) $(FRAMEWORKS) -o $(NAME) $(OBJ)
		rm -rf $(OBJ)
libft:
		make -C $(LIBFT)

clean:
		rm -rf $(OBJ) libft.a

fclean: clean
		make -C minilibx_opengl_20191021 clean
		rm -rf $(NAME)

re: fclean all

run:
	./$(NAME) ./map.cub