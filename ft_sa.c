#include "ft_push_swap.h"

void	ft_sa(t_stack **stack)
{
	t_stack	*cur;
	t_stack	*next;
	t_stack	*temp;

	temp = *stack;
	cur = 0;
	next = 0;
	while (temp)
	{
		cur = temp;
		next = temp->next;
		if (temp->next)
		{
			if (temp->next->next)
				temp = temp->next;
			else
				break ;
		}
		else
			break ;
	}
	if (cur && next)
		ft_swap(&cur->value, &next->value);
}