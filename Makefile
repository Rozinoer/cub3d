NAME = cub3d

CC = gcc

FLAGS = -Wall -Werror -Wextra

FRAMEWORKS = -framework OpenGL -framework Appkit

INCLUDES = -I includes/ -I libft/

GNL_DIR =		res/gnl/

GNL_LIST =		get_next_line.c \
				get_next_line_utils.c \

LIBFT =			res/libft/

SRC_DIR =		src/

SRC_LIST =		cub3d.c \
				key_event.c \

INIT_DIR =		init/

INIT_LIST =		init.c \

PARSE_DIR =		parsing/

PARSE_LIST =	parse.c \
				get_param.c \
				errors.c \
				parsing_utils.c \
				check_map.c \
				get_param1.c \

RENDER_DIR =	render/

RENDER_LIST = 	render_map.c \
				render_player.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

GNL = $(addprefix $(GNL_DIR), $(GNL_LIST))

INIT = $(addprefix $(INIT_DIR), $(INIT_LIST))

PARSE = $(addprefix $(PARSE_DIR), $(PARSE_LIST))

RENDER= $(addprefix $(RENDER_DIR), $(RENDER_LIST))

SRCS = $(SRC) $(GNL) $(INIT) $(PARSE) $(RENDER)

OBJ = $(SRC:.c=.o) $(GNL:.c=.o)

LIBRARY = -L. -lft -lmlx

all: $(NAME)

$(NAME): $(OBJ) libft
		make -C minilibx_opengl_20191021
		mv minilibx_opengl_20191021/libmlx.a .
		cp $(LIBFT)/libft.a .
		$(CC) $(FLAGS) $(SRCS) $(INCLUDES) $(LIBRARY) $(FRAMEWORKS) -o $(NAME)
		make clean

libft:
		make -C $(LIBFT)

%.o: %.c
		gcc -g $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -rf $(OBJ) libft.a

fclean: clean
		make -C minilibx clean
		rm -rf $(NAME)

re: fclean all

run:
	./$(NAME)