#include "push_swap.h"


void		exit_on_err(void)
{
	ft_printf("Error\n");
	exit (1);
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