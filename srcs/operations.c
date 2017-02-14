#include "push_swap.h"

void	rra(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	int		tmp1;
	
	first = stk->a;
	if (!first || first->next == NULL)
		return ;
	tmp = first->nr;	
	last = first->next;
	while (last)
	{
		tmp1 = last->nr;
		last->nr = tmp;
		tmp = tmp1;
		last = last->next;
	}
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec rra", stk, tmp, 0) : ft_printf("rra\n");
}

void	rrb(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	int		tmp1;
	
	first = stk->b;
	if (!first || first->next == NULL)
		return ;
	tmp = first->nr;	
	last = first->next;
	while (last)
	{
		tmp1 = last->nr;
		last->nr = tmp;
		tmp = tmp1;
		last = last->next;
	}
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec rrb", stk, tmp, 0) : ft_printf("rrb\n");
}

void	rrr(t_stacks *stk)
{
	rra(stk, 0);
	rrb(stk, 0);
	stk->flags.debug == 1 ? \
		print_stacks("Exec rrr", stk, MAX_INT, 0) : ft_printf("rrr\n");
}