#include "ft_push_swap.h"

t_stack	*ft_new(int value, int flag)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (0);
	stack->value = value;
	stack->flag = flag;
	stack->next = 0;
	return (stack);
}

int	ft_stack_size(t_stack *stack)
{
	if (!stack)
		return (0);
	return (1 + ft_stack_size(stack->next));
}

int	ft_add_front(t_stack **stack, t_stack *new)
{
	t_stack	*ans;

	if (!(*stack))
	{
		*stack = new;
		return (1);
	}
	ans = *stack;
	while (ans->next != 0)
	{
		if (ans->value == new->value)
			return (0);
		ans = ans->next;
	}
	if (ans->value == new->value)
		return (0);
	new->next = *stack;
	*stack = new;
	return (1);
}
