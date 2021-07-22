#include "ft_push_swap.h"

void	ft_sort_three_helper(t_stack **pStack)
{
	t_stack	*stack;

	stack = *pStack;
	if (stack->value < stack->next->value
		&& stack->next->value > stack->next->next->value
		&& stack->value < stack->next->next->value)
	{
		ft_rra(pStack, "rra\n");
		stack = *pStack;
	}
	if (stack->value > stack->next->value
		&& stack->value < stack->next->next->value
		&& stack->next->value < stack->next->next->value)
	{
		ft_ra(pStack, "ra\n");
	}
}

void	ft_sort_three(t_stack **pStack)
{
	t_stack	*stack;

	stack = *pStack;
	if (stack->value > stack->next->value
		&& stack->next->value < stack->next->next->value
		&& stack->value > stack->next->next->value)
	{
		ft_sa(pStack, "sa\n");
		stack = *pStack;
	}
	if (stack->value < stack->next->value
		&& stack->next->value < stack->next->next->value)
	{
		ft_sa(pStack, "sa\n");
		stack = *pStack;
	}
	if (stack->value < stack->next->value
		&& stack->next->value > stack->next->next->value
		&& stack->value > stack->next->next->value)
		ft_sa(pStack, "sa\n");
	ft_sort_three_helper(pStack);
}

int	is_sorted(t_stack *pStack)
{
	t_stack	*prev;
	int		counter;

	counter = 1;
	prev = pStack;
	if (pStack)
	{
		pStack = pStack->next;
		while (pStack)
		{
			if (prev->value < pStack->value)
				return (0);
			counter++;
			prev = pStack;
			pStack = pStack->next;
		}
	}
	return (1);
}

void	run(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = ft_stack_size(*stack_a);
	if (size == 1)
		return ;
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		ft_sort_three(stack_a);
	else if (size == 4)
		ft_sort_four(stack_a, stack_b);
	else if (size == 5)
		ft_sort_five(stack_a, stack_b);
	else
		solve(stack_a, stack_b, *stack_a, *stack_b);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**splited;
	int		i;

	i = argc / argc;
	while (argv[i])
	{
		splited = ft_split(argv[i++], ' ');
		if (main_helper(splited, &stack_a) == 1)
		{
			ft_putstr_fd("Error\n", 1);
			return (1);
		}
		ft_free_splited(splited);
	}
	if (is_sorted(stack_a))
	{
		ft_free_stack(&stack_a);
		return (0);
	}
	run(&stack_a, &stack_b);
	moving_for_sort(&stack_a);
	ft_free_stack(&stack_a);
	return (0);
}
