#include "ft_push_swap.h"

void	ft_free_stack(t_stack **stack)
{
	t_stack	*node;
	t_stack	*next;

	node = *stack;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
}

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
