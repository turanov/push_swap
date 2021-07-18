#include "ft_push_swap.h"

void	ft_rb(t_stack **stack, char *str)
{
	t_stack	*prev;
	t_stack	*cur;

	ft_putstr_fd(str, 1);
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
