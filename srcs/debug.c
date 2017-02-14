#include "push_swap.h"

t_stack		*ret_stack_(t_stack *stack, int i)
{
	t_stack	*n;
	int		x;
	
	x = 1;
	n = stack;
	while (n)
	{
		if (x++ == i)
			return (n);
		n = n->next;
	}
	return (NULL);
}

void		cut_the_crap(int *i, int *cut)
{
	*i = 15;
	*cut = 1;
	ft_printf("""`-._,-'""` -.|,-'""` -._,-`\n");
	ft_printf("           *\n           *");
	ft_printf("\n|`-._,-'""`-._,-'""`-._,-`|\n");
}

void		print_stacks(char *oper, t_stacks *stk, int f, int cut)
{
	int			i;
	int			max;
	t_stack		*n;

	i = (max = stk->sza > stk->szb ? stk->sza : stk->szb);
	ft_printf("\n> %s:\n_______________________\n", oper);
	while (i--)
	{
		if (f != MAX_INT && cut == 0 && max > 50 && i < max - 15)
			cut_the_crap(&i, &cut);
		if ((n = ret_stack_(stk->a, max - i)))
			(n->nr == f && stk->flags.color) ? \
		ft_printf("|%s%10 d%s|", G, n->nr, E) : ft_printf("|%10 d|", n->nr);
		else
			ft_printf("|%11  |");
		if ((n = ret_stack_(stk->b, max - i)))
			(n->nr == f && stk->flags.color) ? \
			ft_printf("%s%10 d%s|\n", G, n->nr, E) : \
				ft_printf("%10 d|\n", n->nr);
		else
			ft_printf("%11 |\n");
	}
	ft_printf("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n%7 a %10 b\n\n\n");
}