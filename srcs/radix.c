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

void		radix(int *stack, size_t size)
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
	radix(stk->sorted, size);
	stk->med_val = stk->sorted[size / 2];
}