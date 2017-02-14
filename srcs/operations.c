#include "push_swap.h"

int		pa(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->b == NULL)
		return (-1);
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

int		pb(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->a == NULL)
		return (-1);
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

void	sa(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;

	if (stk->sza >= 2 && stk->a->nr > stk->a->next->nr)
	{
		first = stk->a;
		if (!first || first->next == NULL)
			return ;
		tmp = (first->next)->nr;
		(first->next)->nr = first->nr;
		first->nr = tmp;
		if (print == 1)
			stk->flags.debug == 1 ? \
			print_stacks("Exec sa", stk, tmp, 0) : ft_printf("sa\n");
	}
}

void	sb(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;
	
	if (stk->szb >= 2 && stk->b->nr < stk->b->next->nr)
	{
		first = stk->b;
		if (!first || first->next == NULL)
			return ;
		tmp = (first->next)->nr;
		(first->next)->nr = first->nr;
		first->nr = tmp;
		if (print == 1)
			stk->flags.debug == 1 ? \
			print_stacks("Exec sb", stk, tmp, 0) : ft_printf("sb\n");
	}
}

void	ss(t_stacks *stk)
{
	if ((stk->sza >= 2 && stk->a->nr > stk->a->next->nr) && \
		(stk->szb >= 2 && stk->b->nr < stk->b->next->nr))
	{
		sa(stk, 0);
		sb(stk, 0);
		stk->flags.debug == 1 ? \
			print_stacks("Exec ss", stk, stk->a->nr, 0) : ft_printf("ss\n");
	}
}

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