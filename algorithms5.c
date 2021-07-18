#include "ft_push_swap.h"

void	find_optimal_value(t_stack **stack_a, t_stack **stack_b,
						   t_stack *cur, int min_step)
{
	t_stack	temp_a;
	t_stack	temp_b;
	t_temp	f;

	while (cur)
	{
		if (find_min_step(fun(find_step_a(stack_a, cur->value,
						-2147483648), cur)) < min_step)
		{
			min_step = fund(find_step_a(stack_a, cur->value, -2147483648),
					&temp_a, &temp_b, cur);
			f = fun(find_step_a(stack_a, cur->value, -2147483648), cur);
		}
		cur = cur->next;
	}
	if (f.rr <= f.rrr && f.rr <= f.rr_rrr && f.rr <= f.rrr_rr)
		fun_rr(stack_a, stack_b, temp_a, temp_b);
	else if (f.rrr <= f.rr && f.rrr <= f.rr_rrr && f.rrr <= f.rrr_rr)
		fun_rrr(stack_a, stack_b, temp_a, temp_b);
	else if (f.rr_rrr <= f.rr && f.rr_rrr <= f.rrr && f.rr_rrr <= f.rrr_rr)
		fun_rr2(stack_a, stack_b, temp_a, temp_b);
	else if (f.rrr_rr <= f.rr && f.rrr_rr <= f.rrr && f.rrr_rr <= f.rr_rrr)
		fun_rrr2(stack_a, stack_b, temp_a, temp_b);
	find_optimal_value_help(stack_a, stack_b);
}

void	run_solving(t_stack **stack_a, t_stack **stack_b)
{
	ft_move_from_a_to_b(stack_a, stack_b);
	ft_update_rr_rrr_a(stack_a, ft_stack_size(*stack_a));
	ft_update_rr_rrr_b(stack_b, ft_stack_size(*stack_b));
	while (*stack_b)
	{
		find_optimal_value(stack_a, stack_b, *stack_b, 2147483647);
	}
}

void	solve(t_stack **stack_a, t_stack **stack_b,
			  t_stack *cur, t_stack *value)
{
	int	found_max;
	int	max;
	int	k;

	max = 0;
	k = 0;
	while (cur)
	{
		found_max = find_max_to_remain_in_a2(stack_a, *stack_a, cur->value, &k);
		found_max += find_max_to_remain_in_a2_help(stack_a,
				*stack_a, cur->value, &k);
		k = 0;
		if (found_max > max)
		{
			value = cur;
			max = found_max;
		}
		cur = cur->next;
	}
	k = 0;
	find_max_to_remain_in_a_mark(stack_a, *stack_a, value->value, &k);
	find_max_to_remain_in_a_mark_help(stack_a, *stack_a, value->value, &k);
	run_solving(stack_a, stack_b);
}

void	moving_for_sort_help(t_stack **pStack, t_stack curr)
{
	if (curr.rr - 1 < curr.rrr)
	{
		while (curr.rr - 1 > 0)
		{
			ft_ra(pStack, "ra\n");
			curr.rr--;
		}
	}
	else
	{
		while (curr.rrr + 1 > 0)
		{
			ft_rra(pStack, "rra\n");
			curr.rrr--;
		}
	}
}

void	moving_for_sort(t_stack **pStack)
{
	t_stack	*cur;
	t_stack	curr;

	cur = *pStack;
	curr = *cur;
	while (cur)
	{
		if (cur->value < curr.value)
			curr = *cur;
		cur = cur->next;
	}
	moving_for_sort_help(pStack, curr);
}
