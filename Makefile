# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 19:24:45 by joschmun          #+#    #+#              #
#    Updated: 2025/10/16 21:00:11 by joschmun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# config
NAME	:= philo
CC		:= cc
SRC_DIR	:= src
OBJ_DIR	:= obj

CFLAGS	:=
CFLAGS	+= -O2
CFLAGS	+= -Wall
CFLAGS	+= -Wextra
CFLAGS	+= -Werror
CFLAGS	+= $(ADDFLAGS)

CPPFLAGS	:=
CPPFLAGS	+= -I$(SRC_DIR)

CPPFLAGS	+= -I$(SRC_DIR)/error
CPPFLAGS	+= -I$(SRC_DIR)/init
CPPFLAGS	+= -I$(SRC_DIR)/monitor
CPPFLAGS	+= -I$(SRC_DIR)/routine
CPPFLAGS	+= -I$(SRC_DIR)/run
CPPFLAGS	+= -I$(SRC_DIR)/utils


LDFLAGS	:=

LDLIBS	+= -lreadline
# LDLIBS	+= -ltermcap
# LDLIBS	+= -lncurses

ifeq ($(DEBUG), 1)
	CFLAGS	+= -ggdb3 -O0
	LDFLAGS	+= -ggdb3 -O0
endif

ifeq ($(TSAN), 1)
	CFLAGS	+= -fsanitize=thread
	LDFLAGS	+= -fsanitize=thread
endif

ifeq ($(LSAN), 1)
	CFLAGS	+= -fsanitize=leak
	LDFLAGS	+= -fsanitize=leak
endif

ifeq ($(ASAN), 1)
	CFLAGS	+= -fsanitize=address
	LDFLAGS	+= -fsanitize=address
endif

# sources
SRC		:=

vpath %.c $(SRC_DIR)/error
SRC		+= error.c

vpath %.c $(SRC_DIR)/init
SRC		+= init.c

vpath %.c $(SRC_DIR)/monitor
SRC		+= monitor.c

vpath %.c $(SRC_DIR)/routine
SRC		+= routine.c

vpath %.c $(SRC_DIR)/run
SRC		+= run.c
SRC		+= main.c

vpath %.c $(SRC_DIR)/utils
SRC		+= utils.c

OBJ		:= $(SRC:.c=.o)
OBJ		:= $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	@make fclean
	@make all

valtest:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(ARGS)

heltest:
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

.PHONY: all clean fclean re
.PHONY: valtest heltest
