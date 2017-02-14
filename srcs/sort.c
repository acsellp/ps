#include "push_swap.h"

int			select_top_half(t_stacks *stk, char stack)
{
	t_stack	*s;
	int		count;
	int		ps;

	ps = 0;
	if (stack == 'a') count = stk->sza;
		//stk->pivot = stk->sza / 2;
	else if (stack == 'b') count = stk->szb;
		//stk->pivot = stk->szb / 2;
	while (count != 0)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr >= stk->med_val)
			(stack == 'a') ? (pb(stk, 1) && ++ps) : rb(stk, 1);
		else //if (ps <= stk->pivot)
			(stack == 'a') ? ra(stk, 1) : (pa(stk, 1) && ++ps);
		//if (ps > stk->pivot)
		//	break ;
		count--;
	}
	ft_printf("PBS %d vs stk pivot %d[%d]",ps, stk->pivot,stk->med_val);
	return (ps);
}

int			select_bottom_half(t_stacks *stk, char stack)
{
	t_stack	*s;
	int		count;
	int		ps;

	ps = 0;
	if (stack == 'a' ) count = stk->sza;
		//stk->pivot = stk->sza / 2;
	else if (stack == 'b' ) count = stk->szb;
		//stk->pivot = stk->szb / 2;
	while (count != 0)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr <= stk->med_val)
			(stack == 'a') ? (pb(stk, 1) && ++ps) : rb(stk, 1);
		else //if (ps <= stk->pivot)
			(stack == 'a') ? ra(stk, 1) : (pa(stk, 1) && ++ps);
		//if (ps > stk->pivot)
		//	break ;
		count--;
	}
	ft_printf("PBS %d vs stk pivot %d[%d]",ps, stk->pivot,stk->med_val);
	return (ps);
}

int			descending(t_stack *stack)
{
	t_stack	*n;
	
	n = stack;
	if (!n || !n->next)
		return (1);
	while (n && n->next)
	{
		if (n->nr < (n->next)->nr)
			return (0);
		else
			n = n->next;
	}
	return (1);
}

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

int			ret_min(t_stack *stack)
{
	t_stack *b;
	int		min;
	
	b = stack;
	if (b)
		min = b->nr;
	while (b)
	{
		if (min > b->nr)
			min = b->nr;
		b = b->next;
	}
	return (min);
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

int			ret_next_min(t_stack *stack, int curr)
{
	t_stack	*s;
	int		next;
	
	s = stack;
	if (s && s->nr != curr)
		next = s->nr;
	while (s)
	{
		if (next > s->nr && s->nr != curr)
			next = s->nr;
		s = s->next;
	}
	return (next);
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

void		sort_half_a(t_stacks *stk)
{
	int		min;
	size_t	pos;
	int		next_min;
	int		pbs;
	
	stk->ccnt++;
	pbs = 0;
	while (!sorted(stk->a))
	{
		min = ret_min(stk->a);
		if (stk->sza > 2 && stk->a->nr != min)
		{
			ss(stk);
			sb(stk, 1);
			pos = node_pos(min, stk->a);
			next_min = ret_next_min(stk->a, min);
			while (stk->a->nr != min)
			{
				if (stk->a->nr == next_min || stk->a->nr == min)
				{
					pb(stk, 1);
					pbs++;
					next_min = ret_next_min(stk->a, next_min);
				}
				ss(stk);
				sb(stk, 1);
				(pos > stk->sza / 2) ? rra(stk, 1) : ra(stk, 1);
			}
		}
		sa(stk, 1);
		if (!sorted(stk->a) && stk->sza > 2 && ++pbs)
			pb(stk, 1);
	}
	while (pbs-- > 0)
	{
		pa(stk, 1);
		ss(stk);	 
		sa(stk, 1);
		sb(stk, 1);
	}
}

void		sort_half_b(t_stacks *stk)
{
	int		max;
	int		next_max;
	size_t	pos;
	
	while (stk->b)
	{
		max = ret_max(stk->b);
		if (stk->szb > 2 &&  stk->b->nr != max)
		{
			ss(stk);
			sa(stk, 1);
			pos = node_pos(max, stk->b);
			next_max = ret_next_max(stk->b, max);
			while (stk->b->nr != max)
			{
				if (stk->b->nr == next_max || stk->b->nr == max)
				{
					pa(stk, 1);
					next_max = ret_next_max(stk->b, next_max);
				}
				ss(stk);
				sa(stk, 1);
				(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
			}
		}
		sa(stk, 1);
		pa(stk, 1);
	}
}

int			select_top_halfn(t_stacks *stk, char stack, int size)
{
	t_stack		*s;
	int			count;
	int			ps;

	ps = 0;
	count = 0;
	while (count < size && s)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr <= stk->med_val)
			(stack == 'a') ? (pb(stk, 1) && ++ps) : (pa(stk, 1) && ++ps);
		else //if (ps <= stk->pivot)
			(stack == 'a') ? ra(stk, 1) : rb(stk, 1);
		//if (ps > stk->pivot)
		//	break ;
		count++;
	}
	ft_printf("PBS %d vs stk pivot %d[%d]",ps, stk->pivot,stk->med_val);
	return (ps);
}

int			select_halfn(t_stacks *stk, char stack, int top_mid, int low_mid)
{
	t_stack	*s;
	size_t	count;
	int		ps;
	
	ps = 0;
	count = stk->sza;
	while (count)
	{
		s = (stack == 'a') ? stk->a : stk->b;
		if (s->nr >= stk->med_val && s->nr <= top_mid)
		{
			(stack == 'a') ? \
			(pb(stk, 1) && ((stk->b && stk->b->nr <= low_mid) ? rb(stk, 1) : 0) \
			 && ++ps) : pa(stk, 1) && ++ps;
		}
		else
			(stack == 'b') ? rb(stk, 1) : \
				((stk->b && stk->b->nr <= low_mid) ? rr(stk) : ra(stk, 1));
		count--;
	}
	return (ps);
}

int			sorting(t_stacks *stk)
{
	int scan;
	int interv;
	
	//find_middle_in_interval(stk, 'a', stk->sza);
	stk->med_val = 0;
	interv = select_halfn(stk, 'a', 25, 12);
	//scanf("%d",&scan);
	
	stk->med_val = 26;
	interv = select_halfn(stk, 'a', 50, 38);
	//scanf("%d",&scan);
	
	//find_middle_in_interval(stk, 'a', interv - 1);
	stk->med_val = 51;
	interv = select_halfn(stk, 'a', 75, 63);
	//scanf("%d",&scan);
	
	stk->med_val = 76;
	interv = select_halfn(stk, 'a', 100, 88);
	//scanf("%d",&scan);
	
	//return 1;
	//scanf("%d",&scan);
	
	ft_printf("sorting");

	//find_middle_in_interval(stk, 'a', stk->sza);
	//interv = select_first_half(stk, 'a');

	//sort_half_b(stk);
//	return 1;
	int max;
	int	next_max;
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
				if (stk->flags.debug)
					ft_printf("   max [%d] pos [%d]\n",max, (int)pos);
				(pos > stk->szb / 2) ? rrb(stk, 1) : rb(stk, 1);
			}
		}
		pa(stk, 1);
		sa(stk, 1);
	}
	(void)interv;
	(void)scan;
	return 1;
	
	
	
	/*
	find_middle_in_interval(stk, 'a', interv - 1);
	interv = select_first_half(stk, 'a');
	scanf("%d",&scan);
	*/
	
	//ft_printf("begin");
	//sort_(stk);
	//ft_printf("finish");
	
	
	//print_stacks(".........", stk, MIN_INT, 0);
	return 1;
	sort_half_a(stk);
	sort_half_b(stk);

	return (1);
}




int			sort_(t_stacks *stk)
{

	
	sort_half_a(stk);
	
	if (stk->ccnt == 2)
		return 1;
	
	find_middle(stk, 'b');
	select_bottom_half(stk, 'b');
	
	ft_printf("begin");
	sort_(stk);
	ft_printf("finish");
	
	//print_stacks(".........", stk, MIN_INT, 0);
	//return 1;
	sort_half_b(stk);

	return (1);
}




int			sort(t_stacks *stk, int print)
{
	int		min;
	size_t	pos;
	int		next_min;
	
	if (stk->flags.debug && print == 1)
		print_stacks("Init a and b", stk, MIN_INT, 0);
	while (1)
	{
		if (sorted(stk->a))
			break ;
		min = ret_min(stk->a);
		if (stk->sza > 2 &&  stk->a->nr != min)
		{
			pos = node_pos(min, stk->a);
			next_min = ret_next_min(stk->a, min);
			if (pos > stk->sza / 2)
			{
				while (stk->a->nr != min)
				{
					if (stk->a->nr == next_min || stk->a->nr == min)
					{
						pb(stk, print);
						if (stk->szb >= 2 && first(stk->b) < stk->b->next->nr)
							sb(stk, print);
						next_min = ret_next_min(stk->a, next_min);
					}
					else
						rra(stk, print);
				}
			}
			else
			{
				while (stk->a->nr != min)
				{
					if (stk->a->nr == next_min || stk->a->nr == min)
					{
						pb(stk, print);
						if (stk->szb >= 2 && first(stk->b) < stk->b->next->nr)
							sb(stk, print);
						next_min = ret_next_min(stk->a, next_min);
					}
					else
						ra(stk, print);
				}
			}
/*
			if ((stk->sza > 2 && plast(stk->a) > last(stk->a)) && \
				(stk->szb > 2 && plast(stk->b) < last(stk->b)))
				rrr(stk);
			if (stk->sza > 2 && stk->a->nr > last(stk->a))
				rra(stk, 1);
			if (stk->szb > 2 && plast(stk->b) < last(stk->b))
				rrb(stk, 1);		
			
			if ((stk->sza > 2 && stk->a->nr > last(stk->a)) && \
				(stk->szb > 2 && first(stk->b) < last(stk->b)))
				rr(stk);
			if (stk->sza > 2 && stk->a->nr > last(stk->a))
				ra(stk, 1);
			if (stk->szb > 2 && first(stk->b) < last(stk->b))
				rb(stk, 1);	

			if ((stk->sza >= 2 && stk->a->nr > stk->a->next->nr) &&\
				(stk->szb >= 2 && first(stk->b) < stk->b->next->nr))
				ss(stk);
			 
				sa(stk, 1);
			if (stk->szb >= 2 && first(stk->b) < stk->b->next->nr)
				sb(stk, 1);
*/
		}
		if (!sorted(stk->a) && stk->sza > 2)
			pb(stk, print);

		while (!descending(stk->b))
		{
			if (stk->szb >= 2 && first(stk->b) < stk->b->next->nr)
				sb(stk, print);
			if (stk->szb > 2 && plast(stk->b) < last(stk->b))
				rrb(stk, print);
		}
		sa(stk, print);
	}
	while (stk->szb != 0)
		pa(stk, print);
	return (sorted(stk->a));
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