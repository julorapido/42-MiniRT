NAME = MiniRT
SRCS = mini_rt.c render.c v3.c
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra

UNAME = $(shell uname -s)
INCLUDES = -I/usr/include -Imlx -I./includes

ifeq ($(shell uname -s), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR) -Lmlx -lmlx -L/usr/lib/X11 -lXtext -lX11


all: $(MLX_LIB) $(NAME)


$(MLX_LIB):
	@echo "Making Minilibx..."
	@make -C $(MLX_DIR)

$(NAME): 
	gcc $(CFLAGS) $(SRCS) $(INCLUDES) -lm -o $(NAME) $(MLX_FLAGS)

clean:
	@echo "Removing .o files..."
	rm -f $(SRCS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


