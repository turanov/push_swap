#include "ft_push_swap.h"

void	ft_update_rr_rrr_a(t_stack **stack_a, int size)
{
	t_stack	*a;
	int		i;

	a = *stack_a;
	i = 0;
	while (a)
	{
		a->rr = size - i;
		a->rrr = i;
		a = a->next;
		i++;
	}
}

void	ft_update_rr_rrr_b(t_stack **stack_b, int size)
{
	t_stack	*b;
	int		i;

	b = *stack_b;
	i = 1;
	while (b)
	{
		b->rr = size - i;
		b->rrr = i;
		b = b->next;
		i++;
	}
}

void	ft_update_rr_rrr(t_stack **stack_a, t_stack **stack_b)
{
	ft_update_rr_rrr_a(stack_a, ft_stack_size(*stack_a));
	ft_update_rr_rrr_b(stack_b, ft_stack_size(*stack_b));
}

int	fund(t_stack a, t_stack *temp_a, t_stack *temp_b, t_stack *cur)
{
	*temp_a = a;
	*temp_b = *cur;
	return (find_min_step(fun(a, cur)));
}

void	find_optimal_value_help(t_stack **stack_a, t_stack **stack_b)
{
	ft_pa(stack_a, stack_b, "pa\n");
	ft_update_rr_rrr(stack_a, stack_b);
}
