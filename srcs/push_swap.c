#include "push_swap.h"

void		sorting(t_stacks *stk)
{
	int		div;
	size_t	mid;
	
	if (stk->cnt < 40)
	{
		sort_(stk, 0);
		return ;
	}
	else if (stk->cnt < 300)
		div = 4;
	else if (stk->cnt < 600)
		div = 8;
	else
		div = 16;
	mid = stk->cnt / div;
	while (stk->curr_pos + mid < stk->cnt)
	{
		set_middle(stk, mid);
		select_half(stk);
	}
	mid = stk->cnt - stk->curr_pos;
	set_middle(stk, mid);
	select_half(stk);
	push_back(stk, 0, 0);
}

int		sorted(t_stack *stack)
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

int			main(int ac, char **av)
{
	t_stacks	*stk;

	stk = init_stacks();
	check_args(av, &ac, stk);
	if (stk->flags.open_file)
		read_from_file(av[1], stk);
	else
		fill_a(av, 1, ac, stk);
	stk->cnt = stk->sza;
	radix(stk);
	if (stk->flags.debug)
		print_stacks("Init a and b", stk, MAX_INT, 0);
	sorting(stk);
	if (stk->flags.debug)
		print_stacks("Done", stk, MAX_INT, 1);
	if (sorted(stk->a) && stk->flags.debug)
		ft_printf("\n   %s[STACK IS SORTED]%s\n\n",G, E);
	else if (stk->flags.debug)
		ft_printf("\n   %s[STACK IS NOT SORTED]%s\n\n",R, E);
	del_stacks(&stk);
	return (0);
}