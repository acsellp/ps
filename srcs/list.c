#include "push_swap.h"

void		fill_a(char **nbrs, int i, int sz, t_stacks *stk)
{
	long long	nr;
	
	while(i < sz)
	{
		nr = atol_base(nbrs[i], 10);
		if (check_range(nr) || check_doubles(stk->a, nr))
			exit_on_err();
		insert(stk, 'a', nr);
		stk->sza++;
		i++;
	}
}

void		read_from_file(char *file_name, t_stacks *stk)
{
	int		fd;
	char	c;
	char	**nr;
	char	*ret;
	int		size;
	
	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit_on_err();
	size = 0;
	while (read(fd, &c, 1) && ++size);
	close(fd);
	fd = open(file_name, O_RDONLY);
	ret = (char*)malloc(sizeof(char) * size);
	read(fd, ret, size);
	close(fd);
	nr = ft_strsplit(ret, ' ');
	size = 0;
	while (nr[size++]);
	fill_a(nr, 0, size - 1, stk);
	free(ret);
	size = 0;
	while (nr[size])
		free(nr[size++]);
}

t_stacks	*init_stacks(void)
{
	t_stacks	*stk;
	
	stk = (t_stacks*)malloc(sizeof(t_stacks));
	stk->a = NULL;
	stk->b = NULL;
	stk->sza = 0;
	stk->szb = 0;
	stk->med_val = 0;
	stk->low_mid = 0;
	stk->top_mid = 0;
	stk->curr_pos = 0;
	stk->sorted = NULL;
	stk->flags.debug = 0;
	stk->flags.color = 0;
	stk->flags.open_file = 0;
	return (stk);
}

void		del_stacks(t_stacks **stk)
{
	t_stack	*n;
	
	n = (*stk)->a;
	while(n)
	{
		delete(*stk, 'a', n->nr);
		n = n->next;
	}
	n = (*stk)->b;
	while(n)
	{
		delete(*stk, 'b', n->nr);
		n = n->next;
	}
	if ((*stk)->sorted)
		free((*stk)->sorted);
	free(*stk);
}

void		exit_on_err(void)
{
	ft_printf("Error\n");
	exit (1);
}