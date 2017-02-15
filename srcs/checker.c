#include "push_swap.h"

void	check_cmds(char *c, t_stacks **stk)
{
	(!ft_strcmp(c, "pa") && c[2] == '\0') ? pa(*stk, 0) : \
	(!ft_strcmp(c, "pb") && c[2] == '\0') ? pb(*stk, 0) : \
	(!ft_strcmp(c, "sa") && c[2] == '\0') ? msa(*stk, 0) : \
	(!ft_strcmp(c, "sb") && c[2] == '\0') ? msb(*stk, 0) : \
	(!ft_strcmp(c, "ss") && c[2] == '\0') ? mss(*stk, 0) : \
	(!ft_strcmp(c, "ra") && c[2] == '\0') ? ra(*stk, 0) : \
	(!ft_strcmp(c, "rb") && c[2] == '\0') ? rb(*stk, 0) : \
	(!ft_strcmp(c, "rra") && c[2] == 'a' && c[3] == '\0') ? rra(*stk, 0) : \
	(!ft_strcmp(c, "rrb") && c[2] == 'b' && c[3] == '\0') ? rrb(*stk, 0) : \
	(!ft_strcmp(c, "rrr") && c[2] == 'r' && c[3] == '\0') ? rrr(*stk, 0) : \
	(!ft_strcmp(c, "rr") && c[2] == '\0') ? rr(*stk, 0) : exit_on_err(stk);
}

int		main(int ac, char **av)
{
	t_stacks	*stk;
	char		*cmd;
	
	if (ac == 1)
		return (1);
	stk = init_stacks();
	check_args(av, &ac, &stk);
	if (stk->flags.open_file)
		read_from_file(av[1], &stk);
	else
		fill_a(av, 1, ac, &stk);
	while (get_next_line(0, &cmd) != 0)
	{
		check_cmds(cmd, &stk);
		free(cmd);
	}
	(sorted(stk->a) == 1) ? ft_printf("OK\n") : ft_printf("KO\n");
	return (0);
}