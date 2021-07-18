#include "ft_push_swap.h"

void	ft_pa_help(t_stack **stack_a, t_stack *a, t_stack *b, t_stack *prev_b)
{
	while (b->next)
	{
		prev_b = b;
		b = b->next;
	}
	if (!a)
		*stack_a = ft_new(b->value, b->flag);
	else
		a->next = ft_new(b->value, b->flag);
	prev_b->next = NULL;
	b->next = NULL;
	free(b);
}

void	ft_pa(t_stack **stack_a, t_stack **stack_b, char *str)
{
	t_stack	*a;
	t_stack	*b;
	t_stack	*prev_b;

	ft_putstr_fd(str, 1);
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
		ft_pa_help(stack_a, a, b, prev_b);
	}
}
