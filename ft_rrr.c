#include "ft_push_swap.h"

void	ft_rrr(t_stack **stack_a, t_stack **stack_b, char *str)
{
	ft_putstr_fd(str, 1);
	ft_rra(stack_a, 0);
	ft_rrb(stack_b, 0);
}
