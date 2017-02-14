#include "push_swap.h"

long long	atol_base(char *arg, int base)
{
	long long	n;
	int			neg;
	
	neg = 1;
	while (*arg == '\n' || *arg == ' ' || *arg == '\r' || *arg == '\f' \
		   || *arg == '\v')
		arg++;
	if (*arg == '-')
		neg = -1;
	if (*arg == '-' || *arg == '+')
		arg++;
	n = 0;
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			n = n * base + (*arg - '0');
		else if (*arg >= 'a' && *arg <= 'f')
			n = n * base + (*arg - 'a' + 10);
		else if (*arg >= 'A' && *arg <= 'F')
			n = n * base + (*arg - 'A' + 10);
		arg++;
	}
	return (n * neg);
}

int			check_doubles(t_stack *a, int key)
{
	t_stack	*tmp;
	
	tmp = a;
	while (tmp)
	{
		if (tmp->nr == key)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		check_flags(int i, int j, t_stacks *stk, char **av)
{
	if (i == 1 && i++)
		stk->flags.open_file = 1;
	else if (av[i][j] == 'v')
		stk->flags.debug = 1;
	else if (av[i][j] == 'c')
		stk->flags.color = 1;
	else
	{
		del_stacks(&stk);
		exit_on_err();
	}
}

void		check_args(char **av, int *ac, t_stacks *stk)
{
	int	i;
	int j;
	
	i = 1;
	while (i < *ac)
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '-')
				check_flags(i, j, stk, av);
			j++;
		}
		i++;
	}
	if (stk->flags.debug)
		*ac -= 1;
	if (stk->flags.color)
		*ac -= 1;
}

int			check_range(long long key)
{
	if (key > 0 && key > MAX_INT)
		return (1);
	else if (key < 0 && key < MIN_INT)
		return (1);
	return (0);
}