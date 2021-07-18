#include "ft_push_swap.h"

void	fun_rr(t_stack **stack_a, t_stack **stack_b,
			   t_stack temp_a, t_stack temp_b)
{
	int	k;

	k = ft_min(temp_a.rr, temp_b.rr);
	temp_a.rr -= k;
	temp_b.rr -= k;
	while (k-- > 0)
		ft_rr(stack_a, stack_b);
	while (temp_a.rr-- > 0)
		ft_ra(stack_a, "ra\n");
	while (temp_b.rr-- > 0)
		ft_rb(stack_b, "rb\n");
}

void	fun_rrr(t_stack **stack_a, t_stack **stack_b,
				t_stack temp_a, t_stack temp_b)
{
	int	k;

	k = ft_min(temp_a.rrr, temp_b.rrr);
	temp_a.rrr -= k;
	temp_b.rrr -= k;
	while (k-- > 0)
		ft_rrr(stack_a, stack_b);
	while (temp_a.rrr-- > 0)
		ft_rra(stack_a, "rra\n");
	while (temp_b.rrr-- > 0)
		ft_rrb(stack_b, "rrb\n");
}

void	fun_rr2(t_stack **stack_a, t_stack **stack_b,
				t_stack temp_a, t_stack temp_b)
{
	while (temp_a.rr-- > 0)
		ft_ra(stack_a, "ra\n");
	while (temp_b.rrr-- > 0)
		ft_rrb(stack_b, "rrb\n");
}

void	fun_rrr2(t_stack **stack_a, t_stack **stack_b,
				 t_stack temp_a, t_stack temp_b)
{
	while (temp_a.rrr-- > 0)
		ft_rra(stack_a, "rra\n");
	while (temp_b.rr-- > 0)
		ft_rb(stack_b, "rb\n");
}

t_temp	fun(t_stack a, t_stack *cur)
{
	t_temp	f_a;

	f_a.rr = ft_max(a.rr, cur->rr);
	f_a.rrr = ft_max(a.rrr, cur->rrr);
	f_a.rr_rrr = (a.rr) + cur->rrr;
	f_a.rrr_rr = a.rrr + cur->rr;
	return (f_a);
}
