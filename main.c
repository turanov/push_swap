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
	t_stack		*prev;
	int			counter;

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

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**splited;
	int		i;

	i = 1;
	(void)argc;
	while (argv[i])
	{
		splited = ft_split(argv[i], ' ');
		if (main_helper(splited, &stack_a) == 1)
			return (1);
		ft_free_splited(splited);
		i++;
	}
	if (is_sorted(stack_a))
	{
		ft_free_stack(&stack_a);
		return (0);
	}
	solve(&stack_a, &stack_b, stack_a, stack_a);
	moving_for_sort(&stack_a);
	ft_free_stack(&stack_a);
	return (0);
}
