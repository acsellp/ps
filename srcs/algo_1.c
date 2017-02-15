#include "push_swap.h"

int			ret_next_min(t_stack *stack, int curr)
{
	t_stack	*s;
	int		next;
	
	s = stack;
	if (s && s->nr != curr)
		next = s->nr;
	while (s)
	{
		if (next > s->nr && s->nr != curr)
			next = s->nr;
		s = s->next;
	}
	return (next);
}

static void	filter_half_b(t_stacks *stk, int max, int next_max)
{
	size_t	pos;
	
	ss(stk, 1);
	sa(stk, 1);
	next_max = ret_next_max(stk->b, max);
	while (stk->b->nr != max)
	{
		pos = node_pos(max, stk->b);
		if (stk->b->nr == next_max || stk->b->nr == max)
		{
			pa(stk, 1);
			next_max = ret_next_max(stk->b, next_max);
		}
		ss(stk, 1);
		sa(stk, 1);
		(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
	}
}

void		sort_half_b(t_stacks *stk)
{
	int max;
	
	while (stk->b)
	{
		max = ret_max(stk->b);
		if (stk->szb > 2 &&  stk->b->nr != max)
		{
			filter_half_b(stk, max, 0);
		}
		sa(stk, 1);
		pa(stk, 1);
	}
}

int			select_bottom_half(t_stacks *stk, char stack)
{
	t_stack	*s;
	int		count;
	int		ps;

	ps = 0;
	if (stack == 'a' ) count = stk->sza;
	else if (stack == 'b' ) count = stk->szb;
	while (count != 0)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr <= stk->med_val)
			(stack == 'a') ? (pb(stk, 1) && ++ps) : rb(stk, 1);
		else
			(stack == 'a') ? ra(stk, 1) : (pa(stk, 1) && ++ps);
		count--;
	}
	return (ps);
}

void		find_middle(t_stacks *stk, char stack)
{
	t_stack *a;
	size_t	size;
	size_t	i;
	
	size = (stack == 'a') ? stk->sza : stk->szb;
	if (stk->sorted)
	{
		free(stk->sorted);
		stk->sorted = (int*)malloc(sizeof(int) * size);
	}
	else
		stk->sorted = (int*)malloc(sizeof(int) * size);
	i = 0;
	a = (stack == 'a') ? stk->a : stk->b;
	while (a)
	{
		stk->sorted[i++] = a->nr;
		a = a->next;
	}
	radix_(stk->sorted, size);
	stk->med_val = stk->sorted[size / 2];
}