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
	
	
	stk->sorted = (int*)malloc(sizeof(int) * stk->size_a);
	t_stack *a;
	size_t i = 0;
	a = stk->stack_a;
	while (a)
	{
		stk->sorted[i++] = a->nr;
		a = a->next;
	}
	
	
	ft_printf("\n\nsize a %d\n",stk->size_a);
	i = 0;
	while (i < stk->size_a)
		ft_printf("%d ",stk->sorted[i++]);
	radix(stk->sorted, stk->size_a);
	
	
	
	calc_med(sorted);
	//ft_printf("MED %d\n\n",sorted->med);
	stk->med_val = sorted->med_val;
	//print_stacks("startuem", stk, MAX_INT);
	int srt = sort_(stk);
	
	
	//ft_printf("selected %d\n",select_first_half(stk));
	//print_stacks("FIN", sorted, MAX_INT);
	//ft_printf("\nthe middle is %d\n\n",stk->med);
	if (stk->flags.debug)
		print_stacks("Done", stk, MAX_INT, 1);
	if (srt == 1 && stk->flags.debug)
		ft_printf("\nSTACK IS SORTED\n");
	else if (stk->flags.debug)
		ft_printf("\nNOT SORTED\n");
	
	ft_printf("\n\nsize a %d\n",stk->size_a);
	i = 0;
	while (i < stk->size_a)
		ft_printf("%d ",stk->sorted[i++]);
	
	del_stacks(&stk);
	del_stacks(&sorted);
	return (0);
}