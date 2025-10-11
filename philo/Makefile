# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 10:44:56 by eldiaz-c          #+#    #+#              #
#    Updated: 2025/08/18 10:44:56 by eldiaz-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del archivo de la biblioteca
NAME = philo

# Compilador y banderas de compilación
CC = cc
FLAGS = -Wall -Werror -Wextra

# Definir códigos de color
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN =  \033[0;36m
WHITE = \033[0;37m
GREY = \033[0;90m
RESET = \033[0m

# Archivos fuente y archivos objeto
SRC =	philo.c \
		utils.c \

OBJ = $(SRC:.c=.o)

# Regla para crear los archivos objeto (.o)
# -c indica que se debe commpilar el código sin enlazar (crear solo el .o)
# $< representa el archivo de entrada (el .c que se está compilando)
# -o $@ especifica el nombre del archivo de salida que se está generando
.c.o:
	$(CC) $(FLAGS) -c $< -o $@

# Regla para compilar philo
$(NAME): header $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo
	@echo "$(GREEN)<<< philo compiled >>>$(RESET)"
	@echo

# Regla principal que lo compila todo
all: $(NAME)

# Eliminar todos los archivos .o y .a
clean:
	@rm -f $(OBJ) */*.o
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)<<< full clean complete >>>$(RESET)"
	@echo

re: fclean all

norminette:
	@norminette || true
	@echo
	@echo "$(GREEN)<<< norminette check OK >>>$(RESET)"
	@echo

# ASCII Art
header:
	@echo
	@echo "$(GREY)           __    _ __                       __                  ";
	@echo "$(GREY)    ____  / /_  (_) /___  _________  ____  / /_  ___  __________";
	@echo "$(GREY)   / __ \/ __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/";
	@echo "$(GREY)  / /_/ / / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) ";
	@echo "$(GREY) / .___/_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  ";
	@echo "$(GREY)/_/        ____  _________  __  _/_/_  _____/ /_                ";
	@echo "$(GREY)          / __ \/ ___/ __ \/ / / / _ \/ ___/ __/                ";
	@echo "$(GREY)         / /_/ / /  / /_/ / /_/ /  __/ /__/ /_                  ";
	@echo "$(GREY)        / .___/_/   \____/\__, /\___/\___/\__/                  ";
	@echo "$(GREY)       /_/               /____/                                 ";
	@echo " $(RESET) "
	@echo

# Indica que las siguientes reglas no son archivos reales
.PHONY: all clean fclean re	norminette header bonus