#include "push_swap.h"

int			node_pos(int key, t_stack *stack)
{
	t_stack *l;
	int		pos;
	
	l = stack;
	pos = 1;
	while (l)
	{
		if (l->nr == key)
			return (pos);
		pos++;
		l = l->next;
	}
	return (pos);
}

int			ret_max(t_stack *stack)
{
	t_stack *b;
	int		max;
	
	b = stack;
	if (b)
		max = b->nr;
	while (b)
	{
		if (max < b->nr)
			max = b->nr;
		b = b->next;
	}
	return (max);
}

int			ret_next_max(t_stack *stack, int curr)
{
	t_stack	*s;
	int		next;
	
	s = stack;
	if (s && s->nr != curr)
		next = s->nr;
	while (s)
	{
		if (next < s->nr && s->nr != curr)
			next = s->nr;
		s = s->next;
	}
	return (next);
}

int			select_half(t_stacks *stk)
{
	t_stack	*s;
	size_t	count;
	int		ps;
	
	ps = 0;
	count = stk->sza;
	while (count)
	{
		s = stk->a;
		if (s->nr <= stk->top_mid)
		{
			pb(stk, 1);
			(stk->b && stk->b->nr <= stk->low_mid) ? rb(stk, 1) : 0;
		}
		else
			(stk->b && stk->b->nr <= stk->low_mid) ? rr(stk) : ra(stk, 1);
		count--;
	}
	return (ps);
}

void		push_back(t_stacks *stk, int max, int next_max)
{
	size_t	pos;
	
	while (stk->b)
	{
		max = ret_max(stk->b);
		if (stk->szb > 2 &&  stk->b->nr != max)
		{
			next_max = ret_next_max(stk->b, max);
			while (stk->b->nr != max)
			{
				pos = node_pos(max, stk->b);
				if (stk->b->nr == next_max || stk->b->nr == max)
				{
					pa(stk, 1);
					sa(stk, 1);
					next_max = ret_next_max(stk->b, next_max);
				}
				(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
			}
		}
		pa(stk, 1);
		sa(stk, 1);
	}
}

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

t_stacks	*init_stacks(void)
{
	t_stacks	*stk;
	
	stk = (t_stacks*)malloc(sizeof(t_stacks));
	stk->a = NULL;
	stk->b = NULL;
	stk->sza = 0;
	stk->szb = 0;
	stk->med_val = 0;
	stk->pivot = 2;
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
	nr = ft_strsplit(ret, '\n');
	size = 0;
	while (nr[size++]);
	fill_a(nr, 0, size - 1, stk);
	free(ret);
	size = 0;
	while (nr[size])
		free(nr[size++]);
}