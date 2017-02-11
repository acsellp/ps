#include "push_swap.h"

int			select_first_part(t_stacks *stk)
{
	t_stack	*s;
	int		count;
	int		pbs;
	int		pivot;
	
	pbs = 0;
	pivot = stk->size_a / stk->pivot;
	count = stk->size_a;
	while (count != 0)
	{
		s = stk->stack_a;
		if (s->nr <= stk->med_val && ++pbs)
			pb(stk, 1);
		else if (pbs <= pivot)
			ra(stk, 1);
		if (pbs > pivot)
			break ;
		count--;
	}
	return (pbs);
}

void		calc_med(t_stacks *stk)
{
	t_stack		*a;
	int			pos;

	sort(stk, 0);
	a = stk->stack_a;
	pos = stk->size_a / stk->pivot;
	while (a && pos)
	{
		a = a->next;
		if (--pos == 0)
			break ;
	}
	if (a)
		stk->med_val = a->nr;
	else
		stk->med_val = 0;
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

int			sort_(t_stacks *stk)
{
	int		min;
	int		pos;
	int		next_min;
	int		pbs;
	
	if (stk->flags.debug)
		print_stacks("Init a and b", stk, MAX_INT, 0);
	select_first_part(stk);
	if (stk->flags.debug)
		ft_printf("\t\tSELECTED FIRST PART [%d]",stk->med_val);
	//return (0);
	//
	//	SELECT crest part
	//
	pbs = 0;
	while (1)
	{
		if (sorted(stk->stack_a))
			break ;
		min = ret_min(stk->stack_a);
		if (stk->size_a > 2 &&  first(stk->stack_a) != min)
		{
			if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
				(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
				ss(stk);
			if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
				sb(stk, 1);
			
			pos = node_pos(min, stk->stack_a);
			next_min = ret_next_min(stk->stack_a, min);
			if (pos > stk->size_a / 2)
			{
				while (first(stk->stack_a) != min)
				{
					if (stk->stack_a->nr == next_min || stk->stack_a->nr == min)
					{
						pb(stk, 1);
						pbs++;
						
						if (stk->flags.debug)
							ft_printf("\nprev min %d | next one ",next_min);
						next_min = ret_next_min(stk->stack_a, next_min);
						if (stk->flags.debug)
							ft_printf("%d \n\n",next_min);
					}
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
						sb(stk, 1);
					
					rra(stk, 1);
				}
			}
			else
			{
				while (first(stk->stack_a) != min)
				{
					if (stk->stack_a->nr == next_min || stk->stack_a->nr == min)
					{
						pb(stk, 1);
						pbs++;

						if (stk->flags.debug)
							ft_printf("\nprev min %d | next one ",next_min);
						next_min = ret_next_min(stk->stack_a, next_min);
						if (stk->flags.debug)
							ft_printf("%d \n\n",next_min);
					}
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
						sb(stk, 1);
						
					ra(stk, 1);
				}
			}
		}
		else if (stk->size_a <= 3 && first(stk->stack_a) > second(stk->stack_a))
			sa(stk, 1);
		if (!sorted(stk->stack_a) && stk->size_a > 2 && ++pbs)
			pb(stk, 1);
	}
	if (stk->flags.debug)
		ft_printf("\n   SECOND PART DONE\n");

	if (stk->flags.debug)
		ft_printf("\n   MOVING BACK %d nodes\n", pbs);
	while (pbs-- > 0)
	{
		//ft_printf("pbs-- %d\n",pbs);
		
		//
		//	pa -> ss
		//
		pa(stk, 1);
		//printf("\n-[%d]-\n",pbs);
		if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
			(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
			ss(stk);
		if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
			sa(stk, 1);
		if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
			sb(stk, 1);
	}
	if (stk->flags.debug)
		ft_printf("\n   MOVED TO A\n");
	
	int max;
	int	next_max;
	
	
	//
	//	ss !!!!!
	//
	while (1)
	{
		if (!stk->stack_b)
			break ;
		max = ret_max(stk->stack_b);
		if (stk->size_b > 2 &&  first(stk->stack_b) != max)
		{
			if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
				(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
				ss(stk);
			if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
				sa(stk, 1);
			
			pos = node_pos(max, stk->stack_b);
			next_max = ret_next_max(stk->stack_b, max);
			if (pos > stk->size_b / 2)
			{
				while (first(stk->stack_b) != max)
				{
					if (stk->stack_b->nr == next_max || stk->stack_b->nr == max)
					{
						pa(stk, 1);
						if (stk->flags.debug)
							ft_printf("\nprev max %d | next one ",next_max);
						next_max = ret_next_max(stk->stack_b, next_max);
						if (stk->flags.debug)
							ft_printf("%d \n\n",next_max);
					}
					
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
						sa(stk, 1);
					rrb(stk, 1);
					
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
						sa(stk, 1);
				}
			}
			else
			{
				while (first(stk->stack_b) != max)
				{
					if (stk->stack_b->nr == next_max || stk->stack_b->nr == max)
					{
						pa(stk, 1);

						if (stk->flags.debug)
							ft_printf("\nprev max %d | next one ",next_max);
						next_max = ret_next_max(stk->stack_b, next_max);
						if (stk->flags.debug)
							ft_printf("%d \n\n",next_max);
					}
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
						sa(stk, 1);
					rb(stk, 1);
					
					if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
						(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
						ss(stk);
					if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
						sa(stk, 1);
				}
			}

		}
		if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
			sa(stk, 1);
		//if (!sorted(stk->stack_b) && stk->size_b > 2)
			pa(stk, 1);
	}
	
	
	return (sorted(stk->stack_a));
}






int			sort(t_stacks *stk, int print)
{
	int		min;
	int		pos;
	int		next_min;
	
	if (stk->flags.debug && print == 1)
		print_stacks("Init a and b", stk, MIN_INT, 0);
	while (1)
	{
		if (sorted(stk->stack_a))
			break ;
		min = ret_min(stk->stack_a);
		if (stk->size_a > 2 &&  first(stk->stack_a) != min)
		{
			pos = node_pos(min, stk->stack_a);
			next_min = ret_next_min(stk->stack_a, min);
			if (pos > stk->size_a / 2)
			{
				while (first(stk->stack_a) != min)
				{
					if (stk->stack_a->nr == next_min || stk->stack_a->nr == min)
					{
						pb(stk, print);
						if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
							sb(stk, print);
						next_min = ret_next_min(stk->stack_a, next_min);
					}
					else
						rra(stk, print);
				}
			}
			else
			{
				while (first(stk->stack_a) != min)
				{
					if (stk->stack_a->nr == next_min || stk->stack_a->nr == min)
					{
						pb(stk, print);
						if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
							sb(stk, print);
						next_min = ret_next_min(stk->stack_a, next_min);
					}
					else
						ra(stk, print);
				}
			}
/*
			if ((stk->size_a > 2 && plast(stk->stack_a) > last(stk->stack_a)) && \
				(stk->size_b > 2 && plast(stk->stack_b) < last(stk->stack_b)))
				rrr(stk);
			if (stk->size_a > 2 && first(stk->stack_a) > last(stk->stack_a))
				rra(stk, 1);
			if (stk->size_b > 2 && plast(stk->stack_b) < last(stk->stack_b))
				rrb(stk, 1);		
			
			if ((stk->size_a > 2 && first(stk->stack_a) > last(stk->stack_a)) && \
				(stk->size_b > 2 && first(stk->stack_b) < last(stk->stack_b)))
				rr(stk);
			if (stk->size_a > 2 && first(stk->stack_a) > last(stk->stack_a))
				ra(stk, 1);
			if (stk->size_b > 2 && first(stk->stack_b) < last(stk->stack_b))
				rb(stk, 1);	

			if ((stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a)) &&\
				(stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b)))
				ss(stk);
			if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
				sa(stk, 1);
			if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
				sb(stk, 1);
*/
		}
		if (!sorted(stk->stack_a) && stk->size_a > 2)
			pb(stk, print);

		while (!descending(stk->stack_b))
		{
			if (stk->size_b >= 2 && first(stk->stack_b) < second(stk->stack_b))
				sb(stk, print);
			if (stk->size_b > 2 && plast(stk->stack_b) < last(stk->stack_b))
				rrb(stk, print);
		}
		if (stk->size_a >= 2 && first(stk->stack_a) > second(stk->stack_a))
			sa(stk, print);
	}
	while (stk->size_b != 0)
		pa(stk, print);
	return (sorted(stk->stack_a));
}



t_stacks	*init_stacks(void)
{
	t_stacks	*stk;
	
	stk = (t_stacks*)malloc(sizeof(t_stacks));
	stk->stack_a = NULL;
	stk->stack_b = NULL;
	stk->size_a = 0;
	stk->size_b = 0;
	stk->med_val = 0;
	stk->pivot = 2;
	stk->flags.debug = 0;
	stk->flags.color = 0;
	stk->flags.open_file = 0;
	return (stk);
}

void		del_stacks(t_stacks **stk)
{
	t_stack	*n;
	
	n = (*stk)->stack_a;
	while(n)
	{
		delete(*stk, 'a', n->nr);
		n = n->next;
	}
	n = (*stk)->stack_b;
	while(n)
	{
		delete(*stk, 'b', n->nr);
		n = n->next;
	}
	free(*stk);
}

void		fill_stack_a(char **nbrs, int i, int sz, t_stacks *stk)
{
	long long	nr;
	
	while(i < sz)
	{
		nr = atol_base(nbrs[i], 10);
		if (check_range(nr) || check_doubles(stk->stack_a, nr))
			exit_on_err();
		insert(stk, 'a', nr);
		stk->size_a++;
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
	fill_stack_a(nr, 0, size - 1, stk);
	free(ret);
	size = 0;
	while (nr[size])
		free(nr[size++]);
}