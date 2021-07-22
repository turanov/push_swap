#include "ft_push_swap.h"

void	ft_rr(t_stack **stack_a, t_stack **stack_b, char *str)
{
	ft_putstr_fd(str, 1);
	ft_ra(stack_a, 0);
	ft_rb(stack_b, 0);
}
