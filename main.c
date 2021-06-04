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
		printf("order = %2d, %-5d | order = %d, %-5d\n", stack_a->order, stack_a->value, stack_b->order, stack_b->value);
	}
	else if (!stack_a && stack_b)
	{
		ft_print_stack(stack_a, stack_b->next);
		printf("%-15c | order = %d, %-5d\n", ' ', stack_b->order, stack_b->value);
	}
	else if (stack_a && !stack_b)
	{
		ft_print_stack(stack_a->next, stack_b);
		printf("order = %2d, %-5d | %-5c\n", stack_a->order, stack_a->value, ' ');
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
	if (stack->value < stack->next->value && stack->next->value > stack->next->next->value)
	{
		ft_rra(pStack);
		stack = *pStack;
	}
	if (stack->value > stack->next->value && stack->value < stack->next->next->value)
	{
		ft_ra(pStack);
		stack = *pStack;
	}
	if (stack->value < stack->next->value && stack->next->value < stack->next->next->value)
	{
		ft_sa(pStack);
		stack = *pStack;
	}
	if (stack->value >= stack->next->value && stack->next->value >= stack->next->next->value)
		return ;
	ft_sort_three(pStack);
}

void print_arr(int *arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int* a, int* b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

int partition (int *arr, int low, int high)
{
	int pivot;
	int i;
	pivot = arr[high];
	i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void sort_arr(int *arr, int low, int high)
{
	int pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		sort_arr(arr, low, pi - 1);
		sort_arr(arr, pi + 1, high);
	}
}

void ft_get_position_stack(t_stack **pStack, int *arr, int n)
{
	int i;
	t_stack *stack;

	stack = *pStack;
	while (stack)
	{
		i = 0;
		while (i < n)
		{
			if (stack->value == arr[i])
			{
				stack->order = i;
				break;
			}
			i++;
		}
		stack = stack->next;
	}
}

int  ff_find_min_value(t_stack *pStack, int min, int max, int *r)
{
	int k;

	if (pStack)
	{
		k = ff_find_min_value(pStack->next, min, max, r);
		if (k == -1)
		{
			if (pStack->order >= min && pStack->order <= max)
			{
				printf("POS = %d\n", pStack->order);
				printf("R   = %d\n", *r);
				return (*r);
			}
			(*r)++;
			return -1;
		}
		return (*r);
	}
	return (-1);
}

void devide_two_part(t_stack **stack_a, t_stack **stack_b, int min, int max)
{
	int steps;
	int k;

	k = 0;
	steps = ff_find_min_value(*stack_a, min, max, &k);
	printf("steps = %d\n", steps);
	while (steps > 0)
	{
		ft_ra(stack_a);
		steps--;
	}
	ft_pb(stack_b, stack_a);
}

int ff_find_value(t_stack *pStack, int next, int *r)
{
	{
		int k;

		if (pStack)
		{
			k = ff_find_value(pStack->next, next, r);
			if (k == -1)
			{
				if (pStack->order == next)
					return (*r);
				(*r)++;
				return -1;
			}
			return (*r);
		}
		return (-1);
	}
}

void get_sorted_from_b_to_a(t_stack **stack_a, t_stack **stack_b, int next)
{
	int steps;
	int k;

	k = 0;
	steps = ff_find_value(*stack_a, next, &k);
	while (steps > 0)
	{
		ft_rb(stack_b);
		steps--;
	}
	ft_pa(stack_a, stack_b);
	ft_ra(stack_a);
}

void solve(t_stack **stack_a, t_stack **stack_b, int min, int max)
{
	int i;


	if (min <= max)
	{
		i = 0;
		while (i <= max - ((max + min) / 2) - (max + min) % 2)
		{
			devide_two_part(stack_a, stack_b, min, (max + min) / 2);
			i++;
		}
		i = 0;

//		printf("--------------------------\n");
//		ft_print_stack(*stack_a, *stack_b);
//		printf("\n");
		while (i <= max - (max + min) / 2)
		{
			get_sorted_from_b_to_a(stack_a, stack_b, min + i);
			i++;
		}
//		ft_print_stack(*stack_a, *stack_b);
//		printf("--------------------------\n");
		solve(stack_a, stack_b, (max + min) / 2 + 1, max);
	}
}

void ft_sort_stack(t_stack **stack_a, t_stack **stack_b, int deep)
{
	t_stack *stack;
	int a[deep];
	int n = deep;
	stack = *stack_a;

	while (deep-- && stack)
	{
		a[deep] = stack->value;
		stack = stack->next;
	}

//	print_arr(a, n);
	sort_arr(a,0 , n - 1);
	ft_get_position_stack(stack_a, a, n);
//	print_arr(a, n);
//	ft_print_stack(*stack_a, *stack_b);
	solve(stack_a, stack_b, 0, n - 1);
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
				if (ft_add_back(&stack_a, ft_new(ft_atoi(splited[j]), -1), &max, &min) == 0)
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
	ft_sort_stack(&stack_a, &stack_b, ft_stack_size(stack_a));
	printf("ans = %d", g_ans);




//	printf("Init a and b\n");
//	ft_add_back(&stack_a, ft_new(8));
//	ft_add_back(&stack_a, ft_new(5));
//	ft_add_back(&stack_a, ft_new(6));
//	ft_add_back(&stack_a, ft_new(3));
//	ft_add_back(&stack_a, ft_new(1));
//	ft_add_back(&stack_a, ft_new(2));

//	ft_print_stack(stack_a, stack_b);
//	printf("---------\n");
//	ft_sort_three(&stack_a);
//	ft_print_stack(stack_a, stack_b);
//	printf("max = %d\n",max);
//	printf("min = %d\n",min);
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
