#include "push_swap.h"

int		ra(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	
	first = stk->a;
	if (!first || first->next == NULL)
		return (0);
	last = first;
	tmp = first->nr;
	while (last->next)
	{
		last->nr = (last->next)->nr;
		last = last->next;
	}
	last->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec ra", stk, tmp, 0) : ft_printf("ra\n");
	return (1);
}

int		rb(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	
	first = stk->b;
	if (!first || first->next == NULL)
		return (0);
	last = first;
	tmp = first->nr;
	while (last->next)
	{
		last->nr = (last->next)->nr;
		last = last->next;
	}
	last->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec rb", stk, tmp, 0) : ft_printf("rb\n");
	return (1);
}

int		rr(t_stacks *stk)
{
	ra(stk, 0);
	rb(stk, 0);
	stk->flags.debug == 1 ? \
		print_stacks("Exec rr", stk, MAX_INT, 0) : ft_printf("rr\n");
	return (1);
}