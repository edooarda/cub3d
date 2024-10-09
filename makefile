# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: edribeir <edribeir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/10/09 11:21:58 by edribeir      #+#    #+#                  #
#    Updated: 2024/10/09 11:41:45 by edribeir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ./Libft/libft.a

SUB_DIR = .MLX42

MLXLIB = MLX42/build/libmlx42.a

LIBMLX = ./MLX42

FLAGSMLX = -ldl -lglfw -pthread -lm 

SOURCE = 

OBJECTS = $(SOURCE:%.c=%.o)


all: $(MLXLIB) $(NAME)

$(MLXLIB):
	@cmake $(LIBMLX) -DEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C ./Libft

$(NAME): $(LIBFT) $(MLXLIB) $(OBJECTS)
	@cc $(CFLAGS) $(FLAGSMLX) $(OBJECTS) $(LIBFT) $(MLXLIB) -o $(NAME)
	@echo "\n\t LET'S PLAY!! 🎉🎉\n"

%.o:%.c
	@cc $(CFLAGS) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./Libft
	@rm -f $(OBJECTS)
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

