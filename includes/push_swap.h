#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"

#define MAX_INT	2147483647
#define MIN_INT	-2147483648
#define G "\e[7;32m"
#define E "\e[0m"

typedef struct		s_flags
{
	unsigned char	debug;
	unsigned char	color;
	unsigned char	open_file;
}					t_flags;
typedef struct		s_stack
{
	int				nr;
	struct s_stack	*next;
}					t_stack;
typedef struct		s_stacks
{
	t_stack			*stack_a;
	t_stack			*stack_b;
	int				size_a;
	int				size_b;
	int				med_val;
	int				pivot;
	t_flags			flags;
}					t_stacks;

/*
**	operations.c 99985677
*/

void				pa(t_stacks *stk, int print);
void				pb(t_stacks *stk, int print);
void				sa(t_stacks *stk, int print);
void				sb(t_stacks *stk, int print);
void				ss(t_stacks *stk);
void				ra(t_stacks *stk, int print);
void				rb(t_stacks *stk, int print);
void				rr(t_stacks *stk);
void				rra(t_stacks *stk, int print);
void				rrb(t_stacks *stk, int print);
void				rrr(t_stacks *stk);

/*
**	insert.c
*/

void				insert(t_stacks *stk, char stack, int key);
void				delete(t_stacks *stk, char stack, int key);
void				print_stacks(char *oper, t_stacks *stk, int f, int cut);
t_stack				*ret_stack_(t_stack *stack, int i);

/*
**	utils.c
*/

long long			atol_base(char *arg, int base);
int					check_doubles(t_stack *a, int key);
void				check_flags(int i, int j, t_stacks *stk, char **av);
void				check_args(char **av, int *sz, t_stacks *stk);
int					check_range(long long key);
void				exit_on_err(void);

/*
**	sort.c
*/

int					select_first_part(t_stacks *stk);
void				calc_med(t_stacks *stk);
int					node_pos(int key, t_stack *stack);
int					ret_min(t_stack *stack);
t_stacks			*init_stacks(void);
void				del_stacks(t_stacks **stk);
int					sort(t_stacks *stk, int print);
int					sort_(t_stacks *stk);
void				read_from_file(char *file_name, t_stacks *stk);
void				fill_stack_a(char **nbrs, int i, int sz, t_stacks *stk);

/*
**	list.c
*/

int					first(t_stack *stack);
int					second(t_stack *stack);
int					last(t_stack *stack);
int					plast(t_stack *stack);
int					sorted(t_stack *stack);

/*
**	push_swap.c
*/

#endif	