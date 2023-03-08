.PHONY: all $(NAME) clean fclean re run-tests

SRC			=	main.c				\
				src/args_handler.c	\
				src/solver.c		\
				src/map_modifier.c	\
				src/maze_printer.c

NAME		=	dfs-solver

CC			=	gcc

CFLAGS		=	-Wall -Wextra

CPPFLAGS	=	-I include/

OBJ	=	$(SRC:.c=.o)

all:
	make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
