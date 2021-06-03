#include "ft_push_swap.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sa_sb(t_stack **stack)
{
	t_stack	*cur;
	t_stack	*next;
	t_stack	*temp;

	temp = *stack;
	cur = 0;
	next = 0;
	while (temp)
	{
		cur = temp;
		next = temp->next;
		if (temp->next)
		{
			if (temp->next->next)
				temp = temp->next;
			else
				break ;
		}
		else
			break ;
	}
	if (cur && next)
		ft_swap(&cur->content, &next->content);
}

void ft_ss(t_stack **stack_a, t_stack **stack_b)
{
	ft_sa_sb(stack_a);
	ft_sa_sb(stack_b);
}

void ft_pa_pb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *a;
	t_stack *b;
	t_stack *prev_b;

	a = *stack_a;
	b = *stack_b;
	prev_b = b;
	if (a)
		while (a->next)
			a = a->next;
	if (b)
	{
		if (!b->next)
			*stack_b = NULL;
		while (b->next)
		{
			prev_b = b;
			b = b->next;
		}
		if (!a)
			*stack_a = ft_new(b->content);
		else
			a->next = ft_new(b->content);
		prev_b->next = NULL;
		free(b);
	}
}
void ft_ra_rb(t_stack **stack)
{
	t_stack *prev;
	t_stack *cur;

	cur = *stack;
	if (cur)
	{
		if (cur->next)
			while (cur->next)
			{
				prev = cur;
				cur = cur->next;
			}
		prev->next = NULL;
		cur->next = *stack;
		*stack = cur;
	}
}
void ft_rr(t_stack **stack_a, t_stack **stack_b)
{
	ft_ra_rb(stack_a);
	ft_ra_rb(stack_b);
}

void ft_rra_rrb(t_stack **stack)
{
	t_stack *first;
	t_stack *last;

	first = *stack;
	if (first)
		if (first->next)
		{
			*stack = (*stack)->next;
			last = *stack;
			while (last->next)
				last = last->next;
			first->next = NULL;
			last->next = first;
		}
}

void ft_rrr(t_stack **stack_a, t_stack **stack_b)
{
	ft_rra_rrb(stack_a);
	ft_rra_rrb(stack_b);
}