#include <stdio.h>
#include <stdbool.h>
#include "ft_push_swap.h"
#include "libft/libft.h"

int is_ready_to_b();

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
	// 3 1 2
	if (stack->order > stack->next->order && stack->next->order < stack->next->next->order &&
		stack->order > stack->next->next->order)
	{
		ft_sb(pStack,1);
		stack = *pStack;
	}
	// 1 2 3
	if (stack->order < stack->next->order && stack->next->order < stack->next->next->order)
	{
		ft_sb(pStack,1);
		stack = *pStack;
	}
	// 2 < 3 > 1
	if (stack->order < stack->next->order && stack->next->order > stack->next->next->order &&
		stack->order > stack->next->next->order)
	{

		ft_sb(pStack,1);
		stack = *pStack;
	}

	if (stack->order < stack->next->order && stack->next->order > stack->next->next->order &&
		stack->order < stack->next->next->order)
	{
		ft_rrb(pStack,1);
		stack = *pStack;
	}
	if (stack->order > stack->next->order && stack->order < stack->next->next->order &&
		stack->next->order < stack->next->next->order)
	{
		ft_rb(pStack,1);
		stack = *pStack;
	}
//	ft_sort_three(pStack);
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
		if (pStack->order <= flags.mid && i >= max_index_value)
			max_index_value = i;
		pStack = pStack->next;
		i++;
	}
	if (max - max_index_value <= min_index_value)
		return (max - max_index_value);
	return (min_index_value * -1);
}

int get_best_way_for_max(t_stack *pStack, t_flags flags, int max, int *ans)
{
	int i;
	int top;
	int bottom;
	int ret;

	ret = 0;
	top = 0;
	bottom = max;
	i = 1;
	while (pStack)
	{
		if (pStack->order > flags.mid && i >= top)
		{
			top = i;
			ret = 1;
		}
		if (pStack->order > flags.mid && i <= bottom)
		{
			ret = 1;
			bottom = i;
		}
		pStack = pStack->next;
		i++;
	}
	if (top <= max && max - top <= bottom)
		*ans = (max - top);
	else
		*ans = (-bottom);
	return (ret);
}

void ft_print_flags(t_flags *flags)
{
	printf("Next = %d\n", flags->next);
	printf("Mid = %d\n", flags->mid);
	printf("Max = %d\n", flags->max);
}

int is_can_do_rb(t_stack **pStack)
{
	int min;
	int i;
	t_stack *b;

	min = -2147483648;
	b = *pStack;
	i = 0;
	if (b)
	{
		min = b->order;
		while (b->next)
		{
			b = b->next;
			if (min > b->order)
				min = b->order;
			i++;
		}
	}
	return (ft_stack_size(*pStack)- i);
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
				ft_rra(stack_a, 1);
			}
		else
			while (best_way--)
			{
				if (is_can_do_rb(stack_b))
				{
					ft_rr(stack_a, stack_b);
				}
				else
					ft_ra(stack_a,1);
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
			return (1);
		}
	}
	return (0);
}

void fun(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	ft_pa(stack_a, stack_b);
	ft_ra(stack_a,1);
	flags->next++;
}


int find_best_way_next(t_stack *pStack, t_flags flags, int max)
{
	int i;
	int top;
	int bottom;

	top = 0;
	bottom = max;
	i = 1;
	while (pStack)
	{
		if (pStack->order == flags.next && i >= top)
			top = i;
		if (pStack->order == flags.next && i <= bottom)
			bottom = i;
		pStack = pStack->next;
		i++;
	}
	if (top <= max && max - top <= bottom)
		return (max - top);
	return (-bottom);
}

void ft_sort_three_b(t_stack **pStack)
{

}

void ft_sort_four(t_stack **stack_a, t_stack **stack_b)
{
	ft_pa(stack_a, stack_b);
	ft_sort_three(stack_b);
}

int is_top_more_pev(t_stack **pStack)
{
	t_stack *stack;
	t_stack *prev;

	stack = *pStack;
	if (stack)
	{
		prev = stack;
		while (stack->next)
		{
			prev = stack;
			stack = stack->next;
		}
		if (stack->order > prev->order)
			return (1);
	}
	return (0);
}

void ft_sort_five(t_stack **stack_a, t_stack **stack_b)
{
	ft_pa(stack_a, stack_b);
	ft_pa(stack_a, stack_b);
	if (is_top_more_pev(stack_a))
	{
		t_stack *stack = *stack_b;
		// 3 1 2
		int bln = 0;
		if (stack->order > stack->next->order && stack->next->order < stack->next->next->order &&
			stack->order > stack->next->next->order)
		{
			bln = 1;
		}
		// 1 2 3
		if (stack->order < stack->next->order && stack->next->order < stack->next->next->order)
		{
			bln = 1;
		}
		// 2 < 3 > 1
		if (stack->order < stack->next->order && stack->next->order > stack->next->next->order &&
			stack->order > stack->next->next->order)
		{
			bln = 1;
		}
		if (bln)
			ft_ss(stack_a, stack_b);
		else
			ft_sa(stack_a, 1);

	}
	ft_sort_three(stack_b);
}

void get_sorted_from_b_to_a(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	int best_way;
	int size;
	t_stack *b;

	while (flags->next <= flags->mid)
	{
		size = ft_stack_size(*stack_b);
		if (size == 5)
		{
			ft_sort_five(stack_a, stack_b);
			while (flags->next <= flags->mid)
			{
				if (is_next_equal_to_top(stack_a, flags))
				{
					flags->next++;
					ft_ra(stack_a,1);
					continue;
				}
				b = *stack_b;
				if (!b)
				{
					return;
				}
				while (b->next)
					b = b->next;
				b->flag = -1;
				ft_pa(stack_a, stack_b);
				flags->next++;
				ft_ra(stack_a,1);
			}
//			ft_print_stack(*stack_a, *stack_b);
		}
		if (size == 4)
		{
			ft_sort_four(stack_a, stack_b);
//			ft_print_stack(*stack_a, *stack_b);
//			printf("FLAGS \n");
//			ft_print_flags(flags);
			while (flags->next <= flags->mid)
			{
				if (is_next_equal_to_top(stack_a, flags))
				{
					flags->next++;
					ft_ra(stack_a,1);
					continue;
				}
				b = *stack_b;
				if (!b)
				{
					return;
				}
				while (b->next)
					b = b->next;
				b->flag = -1;
				ft_pa(stack_a, stack_b);
				flags->next++;
				ft_ra(stack_a,1);
			}

//			printf("---------------------\n");
//			ft_print_stack(*stack_a, *stack_b);
//			exit(2);
		}
		if (size == 3)
		{
			ft_sort_three(stack_b);

//			ft_print_stack(*stack_a, *stack_b);
//			printf("FLAGS \n");
			while (flags->next <= flags->mid)
			{
				b = *stack_b;
				if (!b)
					return;
//				ft_print_stack(*stack_a, *stack_b);
				while (b->next)
					b = b->next;
				b->flag = -1;
				ft_pa(stack_a, stack_b);
				ft_ra(stack_a,1);
				flags->next++;
			}
			return;
		}
		best_way = find_best_way_next(*stack_b, *flags, (flags->mid + 1) - flags->next);

		if (best_way < 0)
			while (best_way++ < 0)
				ft_rrb(stack_b,1);
		else
			while (best_way--)
				ft_rb(stack_b,1);
		b = *stack_b;
		if (!b)
			return;
		while (b->next)
			b = b->next;
		b->flag = -1;
		ft_pa(stack_a, stack_b);
		ft_ra(stack_a,1);
		flags->next++;
	}
}

int is_2_next_equal_to_2_top(t_stack **pStack, t_flags *flags)
{
	t_stack *stack;
	t_stack *prev;

	stack = *pStack;
	if (stack)
	{

		prev = NULL;
		while (stack->next)
		{

			prev = stack;
			stack = stack->next;
		}
		if (!prev)
			return (0);
		if (prev->order == flags->next && stack->order == flags->next + 1)
			return (1);
	}
	return (0);
}

void devide_2_part_second(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	t_stack *a;

	a = *stack_a;
	while (a && flags->next <= flags->max)
	{
		if (is_2_next_equal_to_2_top(stack_a, flags))
		{
			ft_sa(stack_a,1);
			a = *stack_a;
		}
		if (is_next_equal_to_top(stack_a, flags))
		{
			flags->next++;
			ft_ra(stack_a,1);
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

int is_top_of_a_ready_go_to_b(t_stack *a, t_flags *flags)
{
	while (a->next)
		a = a->next;
	if (a->flag >= 0 && a->order >= flags->next && a->order <= flags->mid)
		return (1);
	return 0;
}

void devide_2_part_third(t_stack **stack_a, t_stack **stack_b, t_flags *flags)
{
	int cnt;
	while (1)
	{
		if (is_2_next_equal_to_2_top(stack_a, flags))
		{
			ft_sa(stack_a,1);
		}
		if (is_next_equal_to_top(stack_a, flags))
		{
			flags->next++;
			ft_ra(stack_a,1);
			update_flags(flags);
		}
		else
			break;
	}
	cnt = flags->next;
	while (cnt <= flags->max)
	{
		if (is_top_of_a_ready_go_to_b(*stack_a, flags))
		{
			ft_pb(stack_b, stack_a);
		}
		else
		{
			if (is_can_do_rb(stack_b))
			{
				ft_rr(stack_a, stack_b);
			}
			else
				ft_ra(stack_a, 1);
		}
		cnt++;
	}
	cnt = flags->mid;
	while (cnt < flags->max)
	{
		ft_rra(stack_a,1);
		cnt++;
	}
}


int sort(t_stack **stack_a, t_stack **stack_b, t_flags flags)
{
	int best_way;
	int cnt;

	cnt = 0;
	int max = flags.max;
	int check = 1;
	while (check)
	{
		check = get_best_way_for_max(*stack_b, flags, max, &best_way);
		if (!check)
			break;
		if (is_next_equal_to_top(stack_b, &flags))
		{
			fun(stack_a, stack_b, &flags);
			check = 1;
		}
		else
		{
			int bln = 1;
			if (best_way < 0)
				while (best_way++ < 0)
				{
					ft_rra(stack_b,1);
					if (is_next_equal_to_top(stack_b, &flags))
					{
						bln = 0;
						fun(stack_a, stack_b, &flags);
					}
					check = 1;
				}
			else
				while (best_way--)
				{
					ft_ra(stack_b,1);
					if (is_next_equal_to_top(stack_b, &flags))
					{
						bln = 0;
						fun(stack_a, stack_b, &flags);
					}
					check = 1;
				}
			if (bln)
			{
				check = 1;
				ft_pa(stack_a, stack_b);
			}
		}
		cnt++;
		max--;

	}
	get_sorted_from_b_to_a(stack_a, stack_b, &flags);
	update_flags(&flags);
	devide_2_part_third(stack_a, stack_b, &flags);
	if (flags.next <= flags.max)
	{
		update_flags(&flags);
		return sort(stack_a, stack_b, flags);
	}
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
	printf("COUNTER = %d\n", g_ans);
	printf("-----------AFTER DIVIDE-----------\n");
	ft_print_stack(*stack_a, *stack_b);
	printf("----------------\n");
	while (flags->next <= flags->mid)
	{
		flags->next = sort(stack_a, stack_b,
						   get_new_flag(flags->next, (flags->mid - flags->next) / 2 + flags->next, flags->mid));
		printf("-----------------\n");
	}
	while (flags->next <= flags->max)
	{
		update_flags(flags);
		devide_2_part_third(stack_a, stack_b, flags);
		update_flags(flags);
		flags->next = sort(stack_a, stack_b, *flags);
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
	int counter = 1;
	if (pStack)
	{
		pStack = pStack->next;
		while (pStack)
		{
			if (prev->order < pStack->order)
			{
				printf("COUNTER = %d\n", counter);
				return (0);
			}
			counter++;
			prev = pStack;
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
	printf("\n------------AFTER SORTING------------\n");
	ft_print_stack(stack_a, stack_b);
	if (is_sorted(stack_a))
		printf("--------------SORTED--------------\n");
	printf("ans = %d", g_ans);


	return 0;
}

//8 14 4 12 5 10 1 15 2 11 7 13 3 6 9