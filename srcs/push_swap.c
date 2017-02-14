#include "push_swap.h"

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
	if (sorted(stk->a))
		ft_printf("    STACK IS SORTED");
	else
		ft_printf("   NOT SORTED");
	

	
	del_stacks(&stk);
	return (0);
}