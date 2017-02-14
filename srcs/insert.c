#include "push_swap.h"

static void	del_head(t_stacks *stk, char stack)
{
	if (stack == 'a')
		stk->a = stk->a->next;
	else if (stack == 'b')
		stk->b = stk->b->next;
}

void		delete(t_stacks *stk, char stack, int key)
{
	t_stack	*tmp;
	t_stack	*prev;
	
	if (stack == 'a')
		tmp = stk->a;
	else if (stack == 'b')
		tmp = stk->b;
	prev = tmp;
	while (tmp)
	{
		if (tmp->nr == key)
		{
			if (tmp == prev)
				del_head(stk, stack);
			else
				prev->next = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void		insert(t_stacks *stk, char stack, int key)
{
	t_stack	*tmp;
	t_stack	*n;
	
	tmp = (stack == 'a') ? stk->a : stk->b;
	if (tmp == NULL)
	{
		tmp = (t_stack*)malloc(sizeof(t_stack));
		tmp->nr = key;
		tmp->next = NULL;
		if (stack == 'a')
			stk->a = tmp;
		else if (stack == 'b')
			stk->b = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		n = (t_stack*)malloc(sizeof(t_stack));
		n->nr = key;
		n->next = NULL;
		tmp->next = n;
	}
}