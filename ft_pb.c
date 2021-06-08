#include "ft_push_swap.h"

void ft_pb(t_stack **stack_a, t_stack **stack_b)
{
	g_ans++;
	printf("pb\n");
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
			*stack_a = ft_new(b->value, b->order, b->flag );
		else
			a->next = ft_new(b->value, b->order, b->flag);
		prev_b->next = NULL;
		free(b);
	}
}