#include "push_swap.h"

int			node_pos(int key, t_stack *stack)
{
	t_stack *l;
	int		pos;
	
	l = stack;
	pos = 1;
	while (l)
	{
		if (l->nr == key)
			return (pos);
		pos++;
		l = l->next;
	}
	return (pos);
}

int			ret_max(t_stack *stack)
{
	t_stack *b;
	int		max;
	
	b = stack;
	if (b)
		max = b->nr;
	while (b)
	{
		if (max < b->nr)
			max = b->nr;
		b = b->next;
	}
	return (max);
}

int			ret_next_max(t_stack *stack, int curr)
{
	t_stack	*s;
	int		next;
	
	s = stack;
	if (s && s->nr != curr)
		next = s->nr;
	while (s)
	{
		if (next < s->nr && s->nr != curr)
			next = s->nr;
		s = s->next;
	}
	return (next);
}

int			select_half(t_stacks *stk)
{
	t_stack	*s;
	size_t	count;
	int		ps;
	
	ps = 0;
	count = stk->sza;
	while (count)
	{
		s = stk->a;
		if (s->nr <= stk->top_mid)
		{
			pb(stk, 1);
			(stk->b && stk->b->nr <= stk->low_mid) ? rb(stk, 1) : 0;
		}
		else
			(stk->b && stk->b->nr <= stk->low_mid) ? rr(stk, 1) : ra(stk, 1);
		count--;
	}
	return (ps);
}

void		push_back(t_stacks *stk, int max, int next_max)
{
	size_t	pos;
	
	while (stk->b)
	{
		max = ret_max(stk->b);
		if (stk->szb > 2 &&  stk->b->nr != max)
		{
			next_max = ret_next_max(stk->b, max);
			while (stk->b->nr != max)
			{
				pos = node_pos(max, stk->b);
				if (stk->b->nr == next_max || stk->b->nr == max)
				{
					pa(stk, 1);
					sa(stk, 1);
					next_max = ret_next_max(stk->b, next_max);
				}
				(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
			}
		}
		pa(stk, 1);
		sa(stk, 1);
	}
}