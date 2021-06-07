#include "ft_push_swap.h"

void	ft_sa(t_stack **stack)
{
	g_ans++;
	t_stack	*cur;
	t_stack	*temp;

	temp = *stack;
	cur = 0;
	if (temp)
	{
		cur = temp;
		temp = temp->next;
		while (temp->next)
		{
			cur = temp;
			temp = temp->next;
		}
		if (cur && temp)
		{
			ft_swap(&cur->value, &temp->value);
			ft_swap(&cur->order, &temp->order);
			ft_swap(&cur->flag, &temp->flag);
		}
	}
}