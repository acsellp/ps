#include "push_swap.h"

static void	swap(unsigned *a, unsigned *b)
{
    unsigned temp;
	
	temp = *a;
    *a = *b;
    *b = temp;
}

static void	rad_sort_u(unsigned *from, unsigned *to, unsigned bit)
{
	unsigned	*lft;
	unsigned	*rgt;
	
	if (!bit || to < from + 1)
		return;
	lft = from;
	rgt = to - 1;
	while(1)
	{
		while (lft < rgt && !(*lft & bit))
			lft++;
		while (lft < rgt &&  (*rgt & bit))
			rgt--;
		if (lft >= rgt)
			break;
		swap(lft, rgt);
	}
	if (!(bit & *lft) && lft < to)
		lft++;
	bit >>= 1;
	rad_sort_u(from, lft, bit);
	rad_sort_u(lft, to, bit);
}

static void	radix_(int *stack, size_t size)
{
	size_t		i;
	unsigned	*x;
	
	x = (unsigned*)stack;
	i = 0;
	while (i < size)
	{
		x[i] ^= MIN_INT;
		i++;
	}
	rad_sort_u(x, x + size, MIN_INT);
	i = 0;
	while (i < size)
	{
		x[i] ^= MIN_INT;
		i++;
	}
}

void		radix(t_stacks *stk)
{
	t_stack *a;
	int		i;
	
	if (stk->sorted)
	{
		free(stk->sorted);
		stk->sorted = (int*)malloc(sizeof(int) * stk->sza);
	}
	else
		stk->sorted = (int*)malloc(sizeof(int) * stk->sza);
	a = stk->a;
	i = 0;
	while (a)
	{
		stk->sorted[i++] = a->nr;
		a = a->next;
	}
	radix_(stk->sorted, stk->sza);
}

void		set_middle(t_stacks *stk, size_t top)
{
	stk->low_mid = stk->sorted[stk->curr_pos + top / 2];
	stk->top_mid = stk->sorted[stk->curr_pos + top];
	stk->curr_pos += top;
}