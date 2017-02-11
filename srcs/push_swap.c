#include "push_swap.h"

int			main(int ac, char **av)
{
	t_stacks	*stk;
	t_stacks	*sorted;

	stk = init_stacks();
	check_args(av, &ac, stk);
	if (stk->flags.open_file)
		read_from_file(av[1], stk);
	else
		fill_stack_a(av, 1, ac, stk);

	sorted = init_stacks();
	if (stk->flags.open_file)
		read_from_file(av[1], sorted);
	else
		fill_stack_a(av, 1, ac, sorted);
	//sort(stk, 1);
	calc_med(sorted);
	//ft_printf("MED %d\n\n",sorted->med);
	stk->med_val = sorted->med_val;
	//print_stacks("startuem", stk, MAX_INT);
	sort_(stk);
	//ft_printf("selected %d\n",select_first_half(stk));
	//print_stacks("FIN", sorted, MAX_INT);
	//ft_printf("\nthe middle is %d\n\n",stk->med);
	if (stk->flags.debug)
		print_stacks("Done", stk, MAX_INT, 1);
	del_stacks(&stk);
	del_stacks(&sorted);
	return (0);
}