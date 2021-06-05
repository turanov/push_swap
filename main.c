#include <stdio.h>
#include <stdbool.h>
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
		printf("flag = %d  order = %2d, %-5d | flag = %d  order = %d, %-5d\n", stack_a->flag, stack_a->order,
			   stack_a->value,
			   stack_b->flag, stack_b->order, stack_b->value);
	}
	else if (!stack_a && stack_b)
	{
		ft_print_stack(stack_a, stack_b->next);
		printf("%-27c | flag = %d  order = %d, %-5d\n", ' ', stack_b->flag, stack_b->order, stack_b->value);
	}
	else if (stack_a && !stack_b)
	{
		ft_print_stack(stack_a->next, stack_b);
		printf("flag = %d  order = %2d, %-5d | %-5c\n", stack_a->flag, stack_a->order, stack_a->value, ' ');
	}
}

void ft_free_splited(char **splited)
{
	int i;

	if (!*splited || !splited)
		return;
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
		return;
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

void swap(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

int partition(int *arr, int low, int high)
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
				stack->order = i + 1;
				break;
			}
			i++;
		}
		stack = stack->next;
	}
}

t_flags *ft_new_flag(int next, int mid, int max)
{
	t_flags *flag;

	flag = malloc(sizeof(t_flags));
	if (!flag)
		return (NULL);
	flag->next = next;
	flag->mid = mid;
	flag->max = max;
	return (flag);
}

int get_best_way_for_min(t_stack *pStack, t_flags flags, int max)
{
	int i;
	int min_index_value;
	int max_index_value;

	min_index_value = flags.mid;
	max_index_value = flags.next;
	i = 1;
	while (pStack)
	{
		if (pStack->order <= flags.mid && i <= min_index_value)
			min_index_value = i;
		if (pStack->order <= flags.mid  && i >= max_index_value)
			max_index_value = i;
		pStack = pStack->next;
		i++;
	}
	if (max - max_index_value <= min_index_value)
		return (max - max_index_value);
	return (min_index_value * -1);
}

int get_best_way_for_max(t_stack *pStack, t_flags flags, int max)
{
	int i;
	int min_index_value;
	int max_index_value;

	min_index_value = flags.mid;
	max_index_value = flags.next;
	i = 1;
	while (pStack)
	{
		if (pStack->order > flags.mid && i <= min_index_value)
			min_index_value = i;
		if (pStack->order > flags.mid && i >= max_index_value)
			max_index_value = i;
		pStack = pStack->next;
		i++;
	}
	if (max - max_index_value <= min_index_value)
		return (max - max_index_value);
	return (min_index_value * -1);
}

void ft_print_flags(t_flags *flags)
{
	printf("Next = %d\n", flags->next);
	printf("Mid = %d\n", flags->mid);
	printf("Max = %d\n", flags->max);
}

void devide_2_part(t_stack **stack_a, t_stack **stack_b, t_flags flags)
{
	int best_way;
	int cnt;
	cnt = 0;

	while (cnt < flags.mid)
	{
		best_way = get_best_way_for_min(*stack_a, flags, flags.max - cnt);
		if (best_way < 0)
			while (best_way++ < 0)
			{
				ft_rra(stack_a);
			}
		else
			while (best_way--)
			{
				ft_ra(stack_a);
			}
		ft_pb(stack_b, stack_a);
		cnt++;
	}
}

int is_next_equal_to_top(t_stack **pStack, t_flags *flags)
{
	t_stack *stack;

	stack = *pStack;
	if (stack)
	{
		while (stack->next)
			stack = stack->next;
		if (stack->order == flags->next)
		{
			stack->flag = -1;
			stack->order = -4;
			return (1);
		}
	}
	return (0);
}

void fun(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	ft_pa(stack_a, stack_b);
	ft_ra(stack_a);
	flags->next++;
}


int find_best_way_next(t_stack *pStack, t_flags flags, int max)
{
	int i;
	int min_index_value;
	int max_index_value;

	min_index_value = flags.mid;
	max_index_value = flags.next;
	i = 1;
	while (pStack)
	{
		if (pStack->order == flags.next && i <= min_index_value)
			min_index_value = i;
		if (pStack->order == flags.next && i >= max_index_value)
			max_index_value = i;
		pStack = pStack->next;
		i++;
	}
	if (max - max_index_value <= min_index_value)
		return (max - max_index_value);
	return (min_index_value * -1);
}

void get_sorted_from_b_to_a(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{

//	ft_print_stack(*stack_a, *stack_b);
	int best_way;
	t_stack *b;

	ft_print_flags(flags);
	while (flags->next <= flags->mid )
	{
		best_way = find_best_way_next(*stack_b, *flags, flags->max - flags->next);
		ft_print_stack(*stack_a, *stack_b);
		if (best_way < 0)
			while (best_way++ < 0)
				ft_rra(stack_b);
		else
			while (best_way--)
				ft_ra(stack_b);		b = *stack_b;
		ft_print_flags(flags);
		while (b->next)
			b = b->next;
		b->flag = -1;
		ft_pa(stack_a, stack_b);
		ft_ra(stack_a);
		flags->next++;
	}
}

void devide_2_part_second(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	t_stack *a;

	a = *stack_a;
	while (a)
	{
		if (is_next_equal_to_top(stack_a, flags))
		{
			flags->next++;
			ft_ra(stack_a);
			a = *stack_a;
		}
		if (a->flag >= 0 && a->order >= flags->next && a->order <= flags->max)
		{
			ft_pb(stack_b, stack_a);
			a = *stack_a;
		}
		a = a->next;
	}
}

void update_flags(t_flags *flags)
{
	flags->mid = (flags->max - flags->next) / 2 + flags->next;
}

int sort(t_stack **stack_a, t_stack **stack_b, t_flags flags, int max)
{
	int best_way;
	int cnt;

	cnt = 0;
	while (cnt < flags.mid)
	{
		best_way = get_best_way_for_max(*stack_b, flags, max - cnt);
		if (is_next_equal_to_top(stack_b, &flags))
			fun(stack_a, stack_b, &flags);
		else
		{
			int bln = 1;
			if (best_way < 0)
				while (best_way++ < 0)
				{
					ft_rra(stack_b);
					if (is_next_equal_to_top(stack_b, &flags))
					{
						bln = 0;
						fun(stack_a, stack_b, &flags);
					}
				}
			else
				while (best_way--)
				{
					ft_ra(stack_b);
					if (is_next_equal_to_top(stack_b, &flags))
					{
						bln = 0;
						fun(stack_a, stack_b, &flags);
					}
				}
			if (bln)
				ft_pb(stack_a, stack_b);
		}
		cnt++;
	}

	ft_print_stack(*stack_a, *stack_b);
	printf("1--------------------\n");

	ft_print_flags(&flags);
	get_sorted_from_b_to_a(stack_a, stack_b, &flags);

	ft_print_stack(*stack_a, *stack_b);
	printf("1--------------------\n");
//	return 1000;
	update_flags(&flags);
	devide_2_part_second(stack_a, stack_b, &flags);
	if (flags.next <= flags.max)
		return sort(stack_a, stack_b, flags, max - flags.next);
	return (flags.next);
}

t_flags get_new_flag(int next, int mid, int max)
{
	t_flags flag;
	flag.next = next;
	flag.mid = mid;
	flag.max = max;
	return flag;
}

void solve(t_stack **stack_a, t_stack **stack_b, int min, int max)
{
	t_flags *flags;

	flags = ft_new_flag(1, max / 2 + min, max);
	if (!flags)
		return;
	devide_2_part(stack_a, stack_b, *flags);
	ft_print_stack(*stack_a, *stack_b);
	printf("---------------------\n");
	while (flags->next <= flags->mid)
	{
		flags->next = sort(stack_a, stack_b,
get_new_flag(flags->next,(flags->mid - flags->next) / 2 + flags->next, flags->mid),
		flags->mid);
	}
	ft_print_stack(*stack_a, *stack_b);
	printf("---------------------\n");
	update_flags(flags);
	devide_2_part_second(stack_a, stack_b, flags);
	update_flags(flags);
	while (flags->next <= flags->mid)
	{
		flags->next = sort(stack_a, stack_b, *flags, flags->max);
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
	sort_arr(a, 0, n - 1);
	ft_get_position_stack(stack_a, a, n);
	solve(stack_a, stack_b, 1, n);
}

int is_sorted(t_stack *pStack)
{
	t_stack *prev;

	prev = pStack;
	if (pStack)
	{
		pStack = pStack->next;
		while (pStack)
		{
			if (prev->value < pStack->value)
				return (0);
			pStack = pStack->next;
		}
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int max = -2147483648;
	int min = 2147483647;
	char **splited;
	int i;
	int j;
	i = 1;
	while (argv[i])
	{
		splited = ft_split(argv[i], ' ');
		j = 0;
		while (splited[j])
		{
			if (validation(splited[j]))
			{
				if (ft_add_back(&stack_a, ft_new(ft_atoi(splited[j]), -1, 0), &max, &min) == 0)
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
	ft_print_stack(stack_a, stack_b);
	if (is_sorted(stack_a))
		printf("SORTED\n");
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
