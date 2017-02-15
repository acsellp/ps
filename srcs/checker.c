#include "push_swap.h"

void	check_cmds(char *cmd, t_stacks **stk, int pp)
{
	if (!ft_strcmp(cmd, "pa") && cmd[2] == '\0')
		pa(*stk, pp);
	else if (!ft_strcmp(cmd, "pb") && cmd[2] == '\0')
		pb(*stk, pp);
	else if (!ft_strcmp(cmd, "sa") && cmd[2] == '\0')
		msa(*stk, pp);
	else if (!ft_strcmp(cmd, "sb") && cmd[2] == '\0')
		msb(*stk, pp);
	else if (!ft_strcmp(cmd, "ss") && cmd[2] == '\0')
		mss(*stk, pp);
	else if (!ft_strcmp(cmd, "ra") && cmd[2] == '\0')
		ra(*stk, pp);
	else if (!ft_strcmp(cmd, "rb") && cmd[2] == '\0')
		rb(*stk, pp);
	else if (!ft_strcmp(cmd, "rra") && cmd[2] == 'a' && cmd[3] == '\0')
		rra(*stk, pp);
	else if (!ft_strcmp(cmd, "rrb") && cmd[2] == 'b' && cmd[3] == '\0')
		rrb(*stk, pp);
	else if (!ft_strcmp(cmd, "rrr") && cmd[2] == 'r' && cmd[3] == '\0')
		rrr(*stk, pp);
	else if (!ft_strcmp(cmd, "rr") && cmd[2] == '\0')
		rr(*stk, pp);
	else
		exit_on_err(stk);
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
		check_cmds(cmd, &stk, 0);
		free(cmd);
	}
	(sorted(stk->a) == 1) ? ft_printf("OK\n") : ft_printf("KO\n");
	return (0);
}