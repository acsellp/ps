#include "push_swap.h"

int			ret_min(t_stack *stack)
{
	t_stack *b;
	int		min;
	
	b = stack;
	if (b)
		min = b->nr;
	while (b)
	{
		if (min > b->nr)
			min = b->nr;
		b = b->next;
	}
	return (min);
}

void		push_to_a(t_stacks *stk, int pbs)
{
	while (pbs-- > 0)
	{
		pa(stk, 1);
		ss(stk, 1);	 
		sa(stk, 1);
		sb(stk, 1);
	}
}

static void	filter_half_a(t_stacks *stk, int next_min, int min, int *pbs)
{
	size_t	pos;
	
	ss(stk, 1);
	sb(stk, 1);
	next_min = ret_next_min(stk->a, min);
	while (stk->a->nr != min)
	{
		pos = node_pos(min, stk->a);
		if (stk->a->nr == next_min || stk->a->nr == min)
		{
			pb(stk, 1);
			*pbs += 1;
			next_min = ret_next_min(stk->a, next_min);
		}
		ss(stk, 1);
		sb(stk, 1);
		(pos > stk->sza / 2) ? rra(stk, 1) : ra(stk, 1);
	}
}

void		srhalf_a(t_stacks *stk, int min)
{
	int		pbs;
	
	pbs = 0;
	while (!sorted(stk->a))
	{
		min = ret_min(stk->a);
		if (stk->sza > 2 && stk->a->nr != min)
			filter_half_a(stk, 0, min, &pbs);
		sa(stk, 1);
		(!sorted(stk->a) && stk->sza > 2 && ++pbs) ? pb(stk, 1) : 0;
	}
	push_to_a(stk, pbs);
}

int			sort_(t_stacks *stk, int cycles)
{
	srhalf_a(stk, 0);
	if (cycles == 2)
		return (1);
	find_middle(stk, 'b');
	select_bottom_half(stk, 'b');;
	sort_(stk, 2);
	sort_half_b(stk);
	return (1);
}