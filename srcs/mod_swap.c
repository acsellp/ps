#include "push_swap.h"

int		mpa(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->b == NULL)
		return (-42);
	new = (t_stack*)malloc(sizeof(t_stack));
	stk->szb > 0 ? stk->szb-- : 0;
	stk->sza++;
	new->nr = stk->b->nr;
	new->next = stk->a;
	stk->a = new;
	delete(stk, 'b', stk->b->nr);
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec pa", stk, stk->a->nr, 0) : ft_printf("pa\n");
	return (1);
}

int		mpb(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->a == NULL)
		return (-42);
	new = (t_stack*)malloc(sizeof(t_stack));
	stk->sza > 0 ? stk->sza-- : 0;
	stk->szb++;
	new->nr = stk->a->nr;
	new->next = stk->b;
	stk->b = new;
	delete(stk, 'a', stk->a->nr);
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec pb", stk, stk->b->nr, 0) : ft_printf("pb\n");
	return (1);
}

int		msa(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;

	first = stk->a;
	if (!first || first->next == NULL)
		return (0);
	tmp = (first->next)->nr;
	(first->next)->nr = first->nr;
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
			print_stacks("Exec sa", stk, tmp, 0) : ft_printf("sa\n");
	return (1);
}

int		msb(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;
	
	first = stk->b;
	if (!first || first->next == NULL)
		return (0);
	tmp = (first->next)->nr;
	(first->next)->nr = first->nr;
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
			print_stacks("Exec sb", stk, tmp, 0) : ft_printf("sb\n");
	return (1);
}

int		mss(t_stacks *stk, int print)
{
	sa(stk, 0);
	sb(stk, 0);
	if (print == 1)
		stk->flags.debug == 1 ? \
			print_stacks("Exec ss", stk, stk->a->nr, 0) : ft_printf("ss\n");
	return (1);
}