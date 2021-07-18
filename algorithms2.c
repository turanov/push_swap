#include "ft_push_swap.h"

int	find_step_a_helper(t_stack *cur, int value, int *max, t_stack *temp)
{
	if (cur->value < value && cur->value > *max)
	{
		*max = cur->value;
		*temp = *cur;
	}
	return (1);
}

t_stack	find_step_a(t_stack **stack_a, int value, int max)
{
	t_stack	temp;
	t_stack	*cur;
	int		idx;
	t_stack	curr;

	cur = *stack_a;
	idx = 0;
	while (cur)
	{
		idx += find_step_a_helper(cur, value, &max, &temp);
		cur = cur->next;
	}
	if (max > -2147483648)
		return (temp);
	cur = *stack_a;
	curr = *cur;
	while (cur)
	{
		if (curr.value < cur->value)
			curr = *cur;
		cur = cur->next;
	}
	return (curr);
}

int	ft_max(int rr, int rrr)
{
	if (rr > rrr)
		return (rr);
	return (rrr);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	find_min_step(t_temp temp)
{
	return (ft_min(ft_min(temp.rr, temp.rrr),
			ft_min(temp.rr_rrr, temp.rrr_rr)));
}
