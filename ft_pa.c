#include "ft_push_swap.h"

void ft_pa(t_stack **stack_a, t_stack **stack_b)
{
	printf("pa\n");
	g_ans++;
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
//14 12 10 15 11 13 9

//6 3 7 2 1 5 4 8

