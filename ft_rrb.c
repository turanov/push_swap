#include "ft_push_swap.h"

void ft_rrb(t_stack **stack)
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