#include "ft_push_swap.h"

void	sort_two(t_stack **stack)
{
	if ((*stack)->value < (*stack)->next->value)
		ft_sa(stack, "sa\n");
}

int	find_min(t_stack **stack_a)
{
	t_stack	*stack;
	int		i;
	int		index;
	int		value;

	value = 2147483647;
	stack = *stack_a;
	i = 1;
	while (stack)
	{
		if (stack->value < value)
		{
			value = stack->value;
			index = i;
		}
		stack = stack->next;
		i++;
	}
	return (index);
}

void	ft_sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	n;

	n = find_min(stack_a);
	if (4 - n < n)
	{
		n = 4 - n;
		while (n--)
			ft_ra(stack_a, "ra\n");
	}
	else
		while (n-- > 0)
			ft_rra(stack_a, "rra\n");
	ft_pb(stack_b, stack_a, "pb\n");
	ft_sort_three(stack_a);
	ft_pa(stack_a, stack_b, "pa\n");
}

void	ft_sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	n;

	n = find_min(stack_a);
	if (5 - n < n)
	{
		n = 5 - n;
		while (n--)
			ft_ra(stack_a, "ra\n");
	}
	else
		while (n-- > 0)
			ft_rra(stack_a, "rra\n");
	ft_pb(stack_b, stack_a, "pb\n");
	ft_sort_four(stack_a, stack_b);
	ft_pa(stack_a, stack_b, "pa\n");
}
