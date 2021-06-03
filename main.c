#include <stdio.h>
#include "ft_push_swap.h"
#include "libft/libft.h"

int check_max_and_min(char *s, int minus)
{
    char *str;
    int len;

    len = ft_strlen(s);
    if (len > 10)
        return (0);
    if (len < 10)
        return (1);
    if (minus)
        str = "2147483648";
    else
        str = "2147483647";
    while (*str)
    {
        if (*str - *s < 0)
            return (0);
        str++;
        s++;
    }
    return (1);
}

int is_digits(char *s)
{
    while (*s)
    {
        if (*s < '0' || *s > '9')
            return (0);
        s++;
    }
    return (1);
}

int validation(char *s)
{
	int minus;

	minus = 0;
	while (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus = 1;
		s++;
	}
	if (is_digits(s))
        return (check_max_and_min(s, minus));
    return (0);
}


void ft_print_stack(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a && stack_b)
	{
		ft_print_stack(stack_a->next, stack_b->next);
		printf("%-5d | %-5d\n", stack_a->content, stack_b->content);
	}
	else if (!stack_a && stack_b)
	{
		ft_print_stack(stack_a, stack_b->next);
		printf("%-5c | %-5d\n", ' ', stack_b->content);
	}
	else if (stack_a && !stack_b)
	{
		ft_print_stack(stack_a->next, stack_b);
		printf("%-5d | %-5c\n",  stack_a->content, ' ');
	}
}

void ft_free_splited(char **splited)
{
	int i;

	if (!*splited || !splited)
		return ;
	while (splited[i])
	{
		free(splited[i++]);
	}
	free(splited);
}

void ft_sort_three(t_stack **pStack)
{
	t_stack *stack;

	stack = *pStack;
	if (stack->content < stack->next->content && stack->next->content > stack->next->next->content)
	{
		ft_rra_rrb(pStack);
		stack = *pStack;
	}
	if (stack->content > stack->next->content && stack->content < stack->next->next->content)
	{
		ft_ra_rb(pStack);
		stack = *pStack;
	}
	if (stack->content < stack->next->content && stack->next->content < stack->next->next->content)
	{
		ft_sa_sb(pStack);
		stack = *pStack;
	}
	if (stack->content >= stack->next->content && stack->next->content >= stack->next->next->content)
		return ;
	ft_sort_three(pStack);
}

void ft_sort_stack(t_stack *pStack, t_stack *pStack1, int max, int min)
{
	long step;
	int n;

	n = 0;
	step = ((long)max - (long)min) / 10;
	while (n--)

}

int main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int max = -2147483648;
	int min = 2147483647;
	char **splited;
	int		i;
	int		j;
	i = 1;
	while (argv[i])
	{
		splited = ft_split(argv[i],' ');
		j = 0;
		while (splited[j])
		{
			if (validation(splited[j]))
			{
				if (ft_add_back(&stack_a, ft_new(ft_atoi(splited[j])), &max, &min) == 0)
				{
					ft_free_stack(&stack_a);
					printf("Error\n");
					return (1);
				}
//				ft_add_back(&stack_b, ft_new(ft_atoi(splited[j])));
			}
			else
			{
				ft_free_stack(&stack_a);
				printf("Error\n");
				return (1);
			}
			j++;
		}
		ft_free_splited(splited);
		i++;
	}
	ft_sort_stack(stack_a, stack_b, max, min);
	printf("Init a and b\n");
//	ft_add_back(&stack_a, ft_new(8));
//	ft_add_back(&stack_a, ft_new(5));
//	ft_add_back(&stack_a, ft_new(6));
//	ft_add_back(&stack_a, ft_new(3));
//	ft_add_back(&stack_a, ft_new(1));
//	ft_add_back(&stack_a, ft_new(2));

	ft_print_stack(stack_a, stack_b);
	printf("---------\n");
//	ft_sort_three(&stack_a);
	ft_print_stack(stack_a, stack_b);
	printf("max = %d\n",max);
	printf("min = %d\n",min);
//	printf("---   | ---\n");
//	printf("%-5c   %-5c\n", 'a', 'b');
//	printf("----------------------------------------------------------------------------------------------------\n");
//	printf("Exec sa:\n");
//	ft_sa_sb(&stack_a);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//	printf("Exec pb pb pb:\n");
//	ft_pa_pb(&stack_b, &stack_a);
//	ft_pa_pb(&stack_b, &stack_a);
//	ft_pa_pb(&stack_b, &stack_a);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//	printf("Exec ra rb (equiv. to rr):\n");
//	ft_ra_rb(&stack_a);
//	ft_ra_rb(&stack_b);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//
//	printf("Exec rra rrb (equiv. to rrr):\n");
//	ft_rrr(&stack_a, &stack_b);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//	printf("Exec sa:\n");
//	ft_sa_sb(&stack_a);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//	printf("Exec pa pa pa:\n");
//	ft_pa_pb(&stack_a, &stack_b);
//	ft_pa_pb(&stack_a, &stack_b);
//	ft_pa_pb(&stack_a, &stack_b);
//	ft_print_stack(stack_a, stack_b);
//	printf("----------------------------------------------------------------------------------------------------\n");
//

//	while (1);

//	ft_add_back(&stack_b, ft_new(0));

//    printf("----------------sa-------------\n");
//    ft_print_stack(stack_a);
//    printf("---------------call------------\n");
//    ft_sa_sb(&stack_a);
//    ft_print_stack(stack_a);
//    printf("----------------sb-------------\n");
//    ft_print_stack(stack_b);
//    printf("---------------call------------\n");
//	ft_sa_sb(&stack_b);
//    ft_print_stack(stack_b);
//    printf("\n");
//    printf("----------------ss-------------\n");
//    ft_ss(&stack_a, &stack_b);
//    printf("stack a\n");
//    ft_print_stack(stack_a);
//	printf("stack b\n");
//    ft_print_stack(stack_b);
//    printf("\n");
//    printf("----------------pa_pb-------------\n");
//	ft_pa_pb(&stack_a, &stack_b);
//    printf("stack a\n");
//    ft_print_stack(stack_a);
//	printf("stack b\n");
//    ft_print_stack(stack_b);
//
//    printf("\n");
//    printf("----------------ra_rb-------------\n");
//	ft_ra_rb(&stack_a);
//    printf("stack a\n");
//    ft_print_stack(stack_a);
//	printf("stack b\n");
//    ft_print_stack(stack_b);
//    printf("\n");
//    printf("----------------rra_rrb-------------\n");
//	ft_rra_rrb(&stack_a);
//    printf("stack a\n");
//    ft_print_stack(stack_a);
//	printf("stack b\n");
//    ft_print_stack(stack_b);
//    printf("\n");
//    printf("----------------ft_rrr-------------\n");
//	ft_rrr(&stack_a, &stack_b);
//    printf("stack a\n");
//    ft_print_stack(stack_a);
//	printf("stack b\n");
//    ft_print_stack(stack_b);
//    printf("\n");



	return 0;
}
