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
	
	find_middle(stk, 'a');
	
	if (stk->flags.debug)
		print_stacks("Init a and b", stk, MAX_INT, 0);
	select_first_half(stk, 'a');
	if (stk->flags.debug)
		ft_printf("\t\tSELECTED FIRST PART [%d]",stk->med_val);
	

	int srt = sort_(stk);
	
	if (stk->flags.debug)
		print_stacks("Done", stk, MAX_INT, 1);
	
	if (srt == 1 && stk->flags.debug)
		ft_printf("\nSTACK IS SORTED\n");
	else if (stk->flags.debug)
		ft_printf("\nNOT SORTED\n");
	
	del_stacks(&stk);
	return (0);
}