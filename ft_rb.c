#include "ft_push_swap.h"

void ft_rb(t_stack **stack, int bln)
{
	if (bln){
		g_ans++;
		printf("rb\n");
	}

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