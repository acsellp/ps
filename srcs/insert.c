#include "push_swap.h"

static void	del_head(t_stacks *stk, char stack)
{
	if (stack == 'a')
		stk->stack_a = stk->stack_a->next;
	else if (stack == 'b')
		stk->stack_b = stk->stack_b->next;
}

void		delete(t_stacks *stk, char stack, int key)
{
	t_stack	*tmp;
	t_stack	*prev;
	
	if (stack == 'a')
		tmp = stk->stack_a;
	else if (stack == 'b')
		tmp = stk->stack_b;
	prev = tmp;
	while (tmp)
	{
		if (tmp->nr == key)
		{
			if (tmp == prev)
				del_head(stk, stack);
			else
				prev->next = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

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

	cut = 1;
	
	i = (max = stk->size_a > stk->size_b ? stk->size_a : stk->size_b);
	ft_printf("\n> %s:\n_______________________\n", oper);
	while (i--)
	{
		if (f != MAX_INT && cut == 0 && max > 50 && i < max - 15)
			cut_the_crap(&i, &cut);
		if ((n = ret_stack_(stk->stack_a, max - i)))
			(n->nr == f && stk->flags.color) ? \
			ft_printf("|%s%10 d%s|", G, n->nr, E) : ft_printf("|%10 d|", n->nr);
		else
			ft_printf("|%11  |");
		if ((n = ret_stack_(stk->stack_b, max - i)))
			(n->nr == f && stk->flags.color) ? \
			ft_printf("%s%10 d%s|\n", G, n->nr, E) : \
				ft_printf("%10 d|\n", n->nr);
		else
			ft_printf("%11 |\n");
	}
	ft_printf("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n%7 a %10 b\n\n\n");
}

void		insert(t_stacks *stk, char stack, int key)
{
	t_stack	*tmp;
	t_stack	*n;
	
	if (stack == 'a')
		tmp = stk->stack_a;
	else
		tmp = stk->stack_b;
	if (tmp == NULL)
	{
		tmp = (t_stack*)malloc(sizeof(t_stack));
		tmp->nr = key;
		tmp->next = NULL;
		if (stack == 'a')
			stk->stack_a = tmp;
		else if (stack == 'b')
			stk->stack_b = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		n = (t_stack*)malloc(sizeof(t_stack));
		n->nr = key;
		n->next = NULL;
		tmp->next = n;
	}
}