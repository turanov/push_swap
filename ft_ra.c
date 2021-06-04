#include "ft_push_swap.h"

void ft_ra(t_stack **stack)
{
	t_stack *prev;
	t_stack *cur;

	cur = *stack;
	if (cur)
	{
		if (cur->next)
		{
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
}