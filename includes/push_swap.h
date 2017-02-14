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
	int				*sorted;
	t_stack			*a;
	t_stack			*b;
	size_t			sza;
	size_t			szb;
	size_t			cnt;
	size_t			curr_pos;
	int				top_mid;
	int				low_mid;
	
	
	int				med_val;
	int				pivot;
	t_flags			flags;
}					t_stacks;

/*
**	operations.c
*/

int					pa(t_stacks *stk, int print);
int					pb(t_stacks *stk, int print);
void				sa(t_stacks *stk, int print);
void				sb(t_stacks *stk, int print);
void				ss(t_stacks *stk);
int					ra(t_stacks *stk, int print);
int					rb(t_stacks *stk, int print);
int					rr(t_stacks *stk);
void				rra(t_stacks *stk, int print);
void				rrb(t_stacks *stk, int print);
void				rrr(t_stacks *stk);

/*
**	insert.c
*/

void				insert(t_stacks *stk, char stack, int key);
void				delete(t_stacks *stk, char stack, int key);

/*
**	debug.c
*/

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



/*
**	algo_1.c
*/

int					ret_min(t_stack *stack);
int					ret_next_min(t_stack *stack, int curr);
void				sort_half_b(t_stacks *stk);
int					select_bottom_half(t_stacks *stk, char stack);
void				find_middle(t_stacks *stk, char stack);
void				srhalf_a(t_stacks *stk, int min, size_t pos, int next_min);
int					sort_(t_stacks *stk, int cycles);

/*
**	sort.c
*/

int					node_pos(int key, t_stack *stack);
int					ret_max(t_stack *stack);
int					ret_next_max(t_stack *stack, int curr);
int					select_half(t_stacks *stk);
void				push_back(t_stacks *stk, int max, int next_max);
void				sorting(t_stacks *stk);
t_stacks			*init_stacks(void);
void				del_stacks(t_stacks **stk);
void				read_from_file(char *file_name, t_stacks *stk);
void				fill_a(char **nbrs, int i, int sz, t_stacks *stk);

/*
**	list.c
*/

void				exit_on_err(void);
int					sorted(t_stack *stack);

/*
**	radix.c
*/

void				radix(t_stacks *stk);
void				radix_(int *stack, size_t size);
void				find_middle(t_stacks *stk, char stack);
void				set_middle(t_stacks *stk, size_t top);

#endif	