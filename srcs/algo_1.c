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

void		sort_half_b(t_stacks *stk)
{
	int max;
	int	next_max;
	size_t	pos;
	
	while (stk->b)
	{
		max = ret_max(stk->b);
		if (stk->szb > 2 &&  stk->b->nr != max)
		{
			ss(stk);
			sa(stk, 1);
			pos = node_pos(max, stk->b);
			next_max = ret_next_max(stk->b, max);
			while (stk->b->nr != max)
			{
				if (stk->b->nr == next_max || stk->b->nr == max)
				{
					pa(stk, 1);
					next_max = ret_next_max(stk->b, next_max);
				}
				ss(stk);
				sa(stk, 1);
				(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
			}
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
		//stk->pivot = stk->sza / 2;
	else if (stack == 'b' ) count = stk->szb;
		//stk->pivot = stk->szb / 2;
	while (count != 0)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr <= stk->med_val)
			(stack == 'a') ? (pb(stk, 1) && ++ps) : rb(stk, 1);
		else //if (ps <= stk->pivot)
			(stack == 'a') ? ra(stk, 1) : (pa(stk, 1) && ++ps);
		//if (ps > stk->pivot)
		//	break ;
		count--;
	}
	ft_printf("PBS %d vs stk pivot %d[%d]",ps, stk->pivot,stk->med_val);
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

void		srhalf_a(t_stacks *stk, int min, size_t pos, int next_min)
{
	int		pbs;
	
	pbs = 0;
	while (!sorted(stk->a))
	{
		min = ret_min(stk->a);
		if (stk->sza > 2 && stk->a->nr != min)
		{
			ss(stk);
			sb(stk, 1);
			next_min = ret_next_min(stk->a, min);
			while (stk->a->nr != min)
			{
				pos = node_pos(min, stk->a);
				if (stk->a->nr == next_min || stk->a->nr == min)
				{
					pb(stk, 1);
					pbs++;
					next_min = ret_next_min(stk->a, next_min);
				}
				ss(stk);
				sb(stk, 1);
				(pos > stk->sza / 2) ? rra(stk, 1) : ra(stk, 1);
			}
		}
		sa(stk, 1);
		(!sorted(stk->a) && stk->sza > 2 && ++pbs) ? pb(stk, 1) : 0;
	}
	while (pbs-- > 0)
	{
		pa(stk, 1);
		ss(stk);	 
		sa(stk, 1);
		sb(stk, 1);
	}
}

int			sort_(t_stacks *stk, int cycles)
{
	srhalf_a(stk, 0, 0, 0);
	if (cycles == 2)
		return (1);
	find_middle(stk, 'b');
	select_bottom_half(stk, 'b');;
	sort_(stk, 2);
	sort_half_b(stk);
	return (1);
}