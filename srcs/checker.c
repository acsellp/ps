#include "push_swap.h"

int		main(int ac, char **av)
{
	t_stacks	*stk;
	char		**cmds;
	
	stk = init_stacks();
	run_cmds();
	if (sorted(stk->a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}