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

int	main_helper(char **splited, t_stack **stack_a)
{
	int	j;

	j = 0;
	while (splited[j])
	{
		if (validation(splited[j]))
		{
			if (ft_add_front(stack_a, ft_new(ft_atoi(splited[j]), 0)) == 0)
			{
				ft_free_splited(splited);
				ft_free_stack(stack_a);
				return (1);
			}
		}
		else
		{
			ft_free_splited(splited);
			ft_free_stack(stack_a);
			return (1);
		}
		j++;
	}
	return (0);
}
