#include "ft_push_swap.h"

int	find_max_to_remain_in_a2(t_stack **pStack, t_stack *cur,
								int value, int *max)
{
	int	cnt;

	if (cur->value == value)
	{
		*max = value;
		return (1);
	}
	cnt = find_max_to_remain_in_a2(pStack, cur->next, value, max);
	if (cnt >= 1)
	{
		if (cur->value >= *max)
		{
			*max = cur->value;
			cnt++;
		}
	}
	return (cnt);
}

int	find_max_to_remain_in_a2_help(t_stack **pStack, t_stack *cur,
									 int value, int *max)
{
	int	cnt;

	if (!cur)
		return (0);
	cnt = find_max_to_remain_in_a2_help(pStack, cur->next, value, max);
	if (cur->value == value)
		return (cnt);
	if (cur->value > *max)
	{
		*max = cur->value;
		return (++cnt);
	}
	return (cnt);
}

int	find_max_to_remain_in_a_mark(t_stack **pStack, t_stack *cur,
									int value, int *max)
{
	int	cnt;

	if (cur->value == value)
	{
		cur->flag = 1;
		*max = value;
		return (1);
	}
	cnt = find_max_to_remain_in_a_mark(pStack, cur->next, value, max);
	if (cnt >= 1)
	{
		if (cur->value >= *max)
		{
			cur->flag = 1;
			*max = cur->value;
			cnt++;
		}
	}
	return (cnt);
}

int	find_max_to_remain_in_a_mark_help(t_stack **pStack, t_stack *cur,
										 int value, int *max)
{
	int	cnt;

	if (!cur)
		return (0);
	cnt = find_max_to_remain_in_a_mark_help(pStack, cur->next, value, max);
	if (cur->value == value)
		return (cnt);
	if (cur->value > *max)
	{
		cur->flag = 1;
		*max = cur->value;
		return (++cnt);
	}
	return (cnt);
}

void	ft_move_from_a_to_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cur;

	while (1)
	{
		cur = *stack_a;
		if (is_emtpy_flag(cur))
			break ;
		while (cur->next)
			cur = cur->next;
		if (cur->flag == 0)
		{
			ft_pb(stack_b, stack_a, "pb\n");
		}
		else
			ft_ra(stack_a, "ra\n");
	}
}
