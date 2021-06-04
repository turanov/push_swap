#include "ft_push_swap.h"

t_stack *ft_new(int value, int order)
{
    t_stack	*stack;

    stack = malloc(sizeof(t_stack));
    if (!stack)
        return (0);
    stack->value = value;
    stack->order = order;
    stack->next = 0;
    return (stack);
}
int	ft_stack_size(t_stack *stack)
{
	if (!stack)
		return (0);
	return (1 + ft_stack_size(stack->next));
}

void find_max_min(int *max, int *min, int value)
{
	if (value > *max)
		*max = value;
	if (value < *min)
		*min = value;
}

int	ft_add_back(t_stack **stack, t_stack *new, int *max, int *min)
{
    t_stack *ans;

    if (!(*stack))
    {
		find_max_min(max, min, new->value);
        *stack = new;
        return (1);
    }
    ans = *stack;
    while (ans->next != 0){
		find_max_min(max, min, new->value);
		if (ans->value == new->value)
			return (0);
		ans = ans->next;
    }
	find_max_min(max, min, new->value);
	if (ans->value == new->value)
		return (0);
    ans->next = new;
	return (1);
}
