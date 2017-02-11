#include "push_swap.h"

void			pa(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->stack_b == NULL)
		return ;
	new = (t_stack*)malloc(sizeof(t_stack));
	stk->size_b > 0 ? stk->size_b-- : 0;
	stk->size_a++;
	new->nr = stk->stack_b->nr;
	new->next = stk->stack_a;
	stk->stack_a = new;
	delete(stk, 'b', stk->stack_b->nr);
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec pa", stk, stk->stack_a->nr, 0) : ft_printf("pa\n");
}

void			pb(t_stacks *stk, int print)
{
	t_stack	*new;
	
	if (stk->stack_a == NULL)
		return ;
	new = (t_stack*)malloc(sizeof(t_stack));
	stk->size_a > 0 ? stk->size_a-- : 0;
	stk->size_b++;
	new->nr = stk->stack_a->nr;
	new->next = stk->stack_b;
	stk->stack_b = new;
	delete(stk, 'a', stk->stack_a->nr);
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec pb", stk, stk->stack_b->nr, 0) : ft_printf("pb\n");
	//if (stk->size_b >= 2 && first(stk->stack_b) < last(stk->stack_b))
	//	rb(stk); 
}

void			sa(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;

	first = stk->stack_a;
	if (!first || first->next == NULL)
		return ;
	tmp = (first->next)->nr;
	(first->next)->nr = first->nr;
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec sa", stk, tmp, 0) : ft_printf("sa\n");
}

void			sb(t_stacks *stk, int print)
{
	t_stack	*first;
	int		tmp;
	
	first = stk->stack_b;
	if (!first || first->next == NULL)
		return ;
	tmp = (first->next)->nr;
	(first->next)->nr = first->nr;
	first->nr = tmp;
	if (print == 1)
		stk->flags.debug == 1 ? \
		print_stacks("Exec sb", stk, tmp, 0) : ft_printf("sb\n");
}

void			ss(t_stacks *stk)
{
	sa(stk, 0);
	sb(stk, 0);
	stk->flags.debug == 1 ? \
		print_stacks("Exec ss", stk, first(stk->stack_a), 0) : ft_printf("ss\n");
}

void			ra(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	
	first = stk->stack_a;
	if (!first || first->next == NULL)
		return ;
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
}

void			rb(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	
	first = stk->stack_b;
	if (!first || first->next == NULL)
		return ;
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
}

void			rr(t_stacks *stk)
{
	ra(stk, 0);
	rb(stk, 0);
	stk->flags.debug == 1 ? \
		print_stacks("Exec rr", stk, MAX_INT, 0) : ft_printf("rr\n");
}

void			rra(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	int		tmp1;
	
	first = stk->stack_a;
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

void			rrb(t_stacks *stk, int print)
{
	t_stack	*last;
	t_stack	*first;
	int		tmp;
	int		tmp1;
	
	first = stk->stack_b;
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

void			rrr(t_stacks *stk)
{
	rra(stk, 0);
	rrb(stk, 0);
	stk->flags.debug == 1 ? \
		print_stacks("Exec rrr", stk, MAX_INT, 0) : ft_printf("rrr\n");
}