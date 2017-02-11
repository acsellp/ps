#include "push_swap.h"

int	first(t_stack *stack)
{
	return (stack->nr);
}

int	second(t_stack *stack)
{
	return ((stack->next)->nr);
}

int	last(t_stack *stack)
{
	t_stack	*s;
	
	s = stack;
	while (s->next)
		s = s->next;
	return (s->nr);
}

int	plast(t_stack *stack)
{
	t_stack	*s;
	
	s = stack;
	while ((s->next)->next)
		s = s->next;
	return (s->nr);
}

int	sorted(t_stack *stack)
{
	t_stack	*n;
	
	n = stack;
	while (n && n->next)
	{
		if (n->nr < (n->next)->nr)
			n = n->next;
		else
			return (0);
	}
	return (1);
}
