NAME = push_swap

PS = srcs/push_swap.c \
		srcs/utils.c \
		srcs/insert.c \
		srcs/sort.c \
		srcs/list.c \
		srcs/operations.c \
		srcs/radix.c \
		srcs/debug.c \
		srcs/algo_1.c \
		srcs/algo_1_1.c \
		srcs/operations_1.c \
		srcs/operations_2.c

CHK = srcs/checker.c \
		srcs/utils.c \
		srcs/insert.c \
		srcs/sort.c \
		srcs/list.c \
		srcs/operations.c \
		srcs/radix.c \
		srcs/debug.c \
		srcs/algo_1.c \
		srcs/algo_1_1.c \
		srcs/mod_swap.c \
		srcs/operations_1.c \
		srcs/operations_2.c \
		srcs/get_next_line.c

INCL = -I./includes/

FLAGS = -Wall -Werror -Wextra

all:
		gcc $(PS) $(FLAGS) $(INCL) -L./srcs/libft -lft -L./srcs/printf -lftprintf -o $(NAME)
		gcc $(CHK) $(FLAGS) $(INCL) -L./srcs/libft -lft -L./srcs/printf -lftprintf -o checker
		
printf:
		make -C srcs/printf fclean && make -C srcs/printf && make clean -C srcs/printf

libft:
		make -C srcs/libft fclean && make -C srcs/libft && make clean -C srcs/libft

fclean : 
		rm -rf checker
		rm -rf $(NAME)

re : fclean all