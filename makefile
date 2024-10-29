# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/09 11:21:58 by edribeir      #+#    #+#                  #
#    Updated: 2024/10/29 18:24:09 by edribeir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CFLAGS = -Wall -Wextra -Werror -g -I Libft
# CFLAGS += -fsanitize=address

LIBFT = ./Libft/libft.a

SUB_DIR = .MLX42

MLXLIB = MLX42/build/libmlx42.a

LIBMLX = ./MLX42

FLAGSMLX = -ldl -lglfw -pthread -lm 

# SOURCE =  temp.c \

SOURCE = main.c \
		main_checkers.c \
		map_checkers.c \
		color_checkers.c \
		textures_checkers.c \
		utils.c \
		cleaner.c \
		raycasting.c \
		player.c \
		draw_elements.c \

OBJECTS = $(SOURCE:%.c=obj/%.o)

OBJ_DIR = obj

all: $(MLXLIB) $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(MLXLIB):
	@cmake $(LIBMLX) -DEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C ./Libft

$(NAME): $(LIBFT) $(MLXLIB) $(OBJECTS)
	@cc $(CFLAGS) $(FLAGSMLX) $(OBJECTS) $(LIBFT) $(MLXLIB) -o $(NAME)
	@echo "\n--------------------------------------------\n"
	@echo "\n\t R-E-A-D-Y! LET'S PLAY!! 🎉🎉\n"
	@echo "\n--------------------------------------------\n"

obj/%.o:%.c | $(OBJ_DIR)
	@cc $(CFLAGS) -c -o $@ $^ 

clean:
	@$(MAKE) clean -C ./Libft
	@rm -rf $(OBJ_DIR)
	@echo "\t OFILES Cleansed ✅!"

fclean: clean
	@$(MAKE) fclean -C $ ./Libft
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@echo "\t ALL Cleansed ✅!"

sub:
	@echo "\t\tUpdating submodules...⌛"
	@git submodule update --init --recursive
	@echo "\t\tSubmodules Updated ✅"

re: fclean all

.PHONY: all clean fclean re sub

