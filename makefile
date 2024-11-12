# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/09 11:21:58 by edribeir      #+#    #+#                  #
#    Updated: 2024/11/12 18:15:59 by jovieira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Project Name
NAME = Cub3d

# Compilation Flags
CFLAGS = -Wall -Wextra -Werror -g -I Libft -I MLX42/include -I/cub3d.h
CFLAGS += -fsanitize=address

# Library Paths
LIBFT = ./Libft/libft.a
MLXLIB = ./MLX42/build/libmlx42.a
LIBMLX = ./MLX42

# MLX Linker Flags
FLAGSMLX = -ldl -lglfw -pthread -lm 

# Source and Object Directories
SRC_DIR = src
OBJ_DIR = obj

# Source Files
SOURCE = main.c \
	init.c \
	main_checkers.c \
	map_checkers.c \
	color_checkers.c \
	textures_checkers.c \
	utils.c \
	cleaner.c \
	raycasting.c \
	player.c \
	draw_elements.c \
	draw_walls.c \
	controls.c

# Generate full paths for source and object files
SRC = $(addprefix $(SRC_DIR)/, $(SOURCE))
OBJECTS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default Target
all: sub $(MLXLIB) $(OBJ_DIR) $(NAME)

# Create Object Directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Object directory created."

# Build MLX42 Library
$(MLXLIB):
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=1
	@make -C $(LIBMLX)/build -j4
	@echo "MLX42 Library built successfully."

# Build Libft Library
$(LIBFT):
	@$(MAKE) -C ./Libft
	@echo "Libft Library built successfully."

# Compile the Project
$(NAME): $(LIBFT) $(MLXLIB) $(OBJECTS)
	@cc $(CFLAGS) $(FLAGSMLX) $(OBJECTS) $(LIBFT) $(MLXLIB) -o $(NAME)
	@echo "\n--------------------------------------------"
	@echo "\n\t R-E-A-D-Y! LET'S PLAY!! 🎉🎉"
	@echo "\n--------------------------------------------"

# Compile Object Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	@cc $(CFLAGS) -c $< -o $@

# Clean Object Files
clean:
	@$(MAKE) clean -C ./Libft
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned."

# Full Clean (including built libraries)
fclean: clean
	@$(MAKE) fclean -C ./Libft
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@echo "All files cleaned."

# Update Git Submodules
sub:
	@echo "Updating submodules..."
	@git submodule update --init --recursive
	@echo "Submodules updated."

# Rebuild the Project
re: fclean all

.PHONY: all clean fclean re sub
