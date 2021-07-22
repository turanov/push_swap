#include "ft_push_swap.h"

int	is_sorted(t_stack *pStack)
{
	t_stack	*prev;

	prev = pStack;
	if (pStack)
	{
		pStack = pStack->next;
		while (pStack)
		{
			if (prev->value < pStack->value)
				return (0);
			prev = pStack;
			pStack = pStack->next;
		}
	}
	return (1);
}

int	check_line(char *line)
{
	if (ft_strncmp(line, "sa", 2) == 0)
		return (1);
	if (ft_strncmp(line, "sb", 2) == 0)
		return (1);
	if (ft_strncmp(line, "ss", 2) == 0)
		return (1);
	if (ft_strncmp(line, "pa", 2) == 0)
		return (1);
	if (ft_strncmp(line, "rra", 3) == 0)
		return (1);
	if (ft_strncmp(line, "rrb", 3) == 0)
		return (1);
	if (ft_strncmp(line, "rrr", 3) == 0)
		return (1);
	if (ft_strncmp(line, "pb", 2) == 0)
		return (1);
	if (ft_strncmp(line, "ra", 2) == 0)
		return (1);
	if (ft_strncmp(line, "rb", 2) == 0)
		return (1);
	if (ft_strncmp(line, "rr", 2) == 0)
		return (1);
	return (0);
}

void	start_sort(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp(line, "sa", 2) == 0)
		ft_sa(stack_a, 0);
	else if (ft_strncmp(line, "sb", 2) == 0)
		ft_sa(stack_b, 0);
	else if (ft_strncmp(line, "ss", 2) == 0)
		ft_ss(stack_a, stack_b, 0);
	else if (ft_strncmp(line, "pa", 2) == 0)
		ft_pa(stack_a, stack_b, 0);
	else if (ft_strncmp(line, "pb", 2) == 0)
		ft_pb(stack_b, stack_a, 0);
	else if (ft_strncmp(line, "rra", 3) == 0)
		ft_rra(stack_a, 0);
	else if (ft_strncmp(line, "rrb", 3) == 0)
		ft_rrb(stack_b, 0);
	else if (ft_strncmp(line, "rrr", 3) == 0)
		ft_rrr(stack_a, stack_b, 0);
	else if (ft_strncmp(line, "ra", 2) == 0)
		ft_ra(stack_a, 0);
	else if (ft_strncmp(line, "rb", 2) == 0)
		ft_rb(stack_b, 0);
	else if (ft_strncmp(line, "rr", 2) == 0)
		ft_rr(stack_a, stack_b, 0);
}

int	solve_checker(t_stack *stack_a, t_stack *stack_b)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, "Error", 5) == 0)
			ft_putstr_fd("Error\n", 1);
		else if (check_line(line) == 1)
			start_sort(line, &stack_a, &stack_b);
		else
		{
			ft_free_stack(&stack_a);
			ft_free_stack(&stack_b);
			free(line);
			ft_putstr_fd("Error\n", 1);
			return (1);
		}
		free(line);
	}
	if (is_sorted(stack_a))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	ft_free_stack(&stack_a);
	free(line);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**splited;
	int		i;

	i = 1;
	if (argc != 1)
	{
		while (argv[i])
		{
			splited = ft_split(argv[i], ' ');
			if (main_helper(splited, &stack_a) == 1)
			{
				ft_putstr_fd("Error\n", 1);
				return (1);
			}
			ft_free_splited(splited);
			i++;
		}
		stack_b = NULL;
		solve_checker(stack_a, stack_b);
	}
	return (0);
}
