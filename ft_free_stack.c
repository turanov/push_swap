#include "ft_push_swap.h"

static void	ft_del(t_stack *stack)
{
	if (!stack)
		return ;
	ft_del(stack->next);
	free(stack);
}

void	ft_free_stack(t_stack **stack)
{
	if (!(*stack))
		return ;
	ft_del(*stack);
	*stack = 0;
}

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}