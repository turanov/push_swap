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
		printf("flag = %d  order = %2d  rr = %3d  rrr = %3d , %-5d| flag = %d  order = %d  rr = %3d  rrr = %3d , %-5d\n", stack_a->flag, stack_a->order,
			    stack_a->rr, stack_a->rrr, stack_a->value,
			   stack_b->flag, stack_b->order, stack_b->rr, stack_b->rrr,stack_b->value);

	}
	else if (!stack_a && stack_b)
	{
		ft_print_stack(stack_a, stack_b->next);
		printf("%-47c | flag = %d  order = %d  rr = %3d  rrr = %3d , %-5d\n", ' ', stack_b->flag, stack_b->order,stack_b->rr, stack_b->rrr, stack_b->value);
	}
	else if (stack_a && !stack_b)
	{
		ft_print_stack(stack_a->next, stack_b);
		printf("flag = %d  order = %2d  rr = %3d  rrr = %3d  , %-5d | %-5c\n", stack_a->flag, stack_a->order,  stack_a->rr, stack_a->rrr,  stack_a->value, ' ');
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


int find_max_to_remain_in_a2(t_stack **pStack, t_stack *cur, int value, int *max)
{
	int cnt;

	if (cur->value == value)
	{
		*max = value;
		return (1);
	}
	cnt = find_max_to_remain_in_a2(pStack, cur->next, value, max);
	if (cnt >= 1)
	{
		if (cur->value >= *max)
		{
			*max = cur->value;
			cnt++;
		}
	}
	return (cnt);
}


int find_max_to_remain_in_a2_help(t_stack **pStack, t_stack *cur, int value, int *max)
{
	int cnt;

	if (!cur)
		return (0);
	cnt = find_max_to_remain_in_a2_help(pStack, cur->next, value, max);
	if (cur->value == value)
		return (cnt);
	if (cur->value > *max)
	{
		*max = cur->value;
		return (++cnt);
	}
	return (cnt);
}
int find_max_to_remain_in_a_mark(t_stack **pStack, t_stack *cur, int value, int *max)
{
	int cnt;

	if (cur->value == value)
	{
		cur->flag = 1;
		*max = value;
		return (1);
	}
	cnt = find_max_to_remain_in_a_mark(pStack, cur->next, value, max);
	if (cnt >= 1)
	{
		if (cur->value >= *max)
		{
			cur->flag = 1;
			*max = cur->value;
			cnt++;
		}
	}
	return (cnt);
}
int find_max_to_remain_in_a_mark_help(t_stack **pStack, t_stack *cur, int value, int *max)
{
	int cnt;

	if (!cur)
		return (0);
	cnt = find_max_to_remain_in_a_mark_help(pStack, cur->next, value, max);
	if (cur->value == value)
		return (cnt);
	if (cur->value > *max)
	{
		cur->flag = 1;
		*max = cur->value;
		return (++cnt);
	}
	return (cnt);
}

int is_emtpy_flag(t_stack *pStack)
{
	while (pStack)
	{
		if (pStack->flag == 0)
			return (0);
		pStack = pStack->next;
	}
	return (1);
}

void ft_move_from_a_to_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *cur;

	while (1)
	{
		cur = *stack_a;
		if (is_emtpy_flag(cur))
			break;
		while (cur->next)
			cur = cur->next;
		if (cur->flag == 0)
		{
			ft_pb(stack_b, stack_a);
		}
		else
			ft_ra(stack_a, 1);
	}
}


t_stack find_step_a(t_stack **stack_a, int value, int size, int *bln)
{
	t_stack *cur;
	int idx;

	cur = *stack_a;
	idx = 0;
	int max = -2147000000;
	t_stack temp;
	while (cur)
	{

		if (cur->value < value && cur->value > max)
		{
			max = cur->value;
			temp = *cur;
		}
		idx++;
		cur = cur->next;
	}
	if (max > -2147000000)
		return (temp);
	cur = *stack_a;
	t_stack curr = *cur;
	while (cur)
	{
		if (cur->value < curr.value)
			curr = *cur;
		cur = cur->next;
	}
	*bln = 1;
	return (curr);
}

int ft_max(int rr, int rrr)
{
	if (rr > rrr)
		return (rr);
	return (rrr);
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
int find_min_step(int rr, int rrr, int rr_rrr, int rrr_rr)
{
	return ft_min(ft_min(rr, rrr), ft_min(rr_rrr, rrr_rr));
}
void ft_update_rr_rrr_a(t_stack **stack_a, int size)
{
	t_stack *a;
	int i;

	a = *stack_a;
	i = 0;
	while (a)
	{
		a->rr = size - i;
		a->rrr = i;
		a = a->next;
		i++;
	}
}

void ft_update_rr_rrr_b(t_stack **stack_b, int size)
{
	t_stack *b;
	int i;

	b = *stack_b;
	i = 1;
	while (b)
	{
		b->rr = size - i;
		b->rrr = i;
		b = b->next;
		i++;
	}
}

void ft_update_rr_rrr(t_stack **stack_a, t_stack **stack_b)
{
	ft_update_rr_rrr_a(stack_a, ft_stack_size(*stack_a));
	ft_update_rr_rrr_b(stack_b, ft_stack_size(*stack_b));
}

int find_optimal_value(t_stack **stack_a, t_stack **stack_b)
{
	t_stack *cur;
	t_stack a;
	int size_a;
	int size_b;
	int index;
	int steps;
	int rr;
	int rrr;
	int rr_rrr;
	int rrr_rr;
	int temp_rr;
	int temp_rrr;
	int temp_rr_rrr;
	int temp_rrr_rr;

	index = 1;
	size_b = ft_stack_size(*stack_b);
	size_a = ft_stack_size(*stack_a);
	cur = *stack_b;
	int step;
	int min_step = 2147483647;
	int value = cur->value;
	t_stack temp_a;
	t_stack temp_b;
	while (cur)
	{
		int bln;
		bln = 0;
		a = find_step_a(stack_a, cur->value, size_a, &bln);
		rr = ft_max(a.rr - bln, cur->rr);
		rrr = ft_max(a.rrr + bln, cur->rrr);
		rr_rrr = (a.rr - bln) + cur->rrr;
		rrr_rr = a.rrr + bln + cur->rr;
		step = find_min_step(rr, rrr, rr_rrr, rrr_rr);
		if (step < min_step)
		{
			temp_a = a;
			printf("BLN = %d\n", bln);
			value = cur->value;
			min_step = step;
			temp_rr = rr;
			temp_rrr = rrr;
			temp_rr_rrr = rr_rrr;
			temp_rrr_rr = rrr_rr;
			temp_b = *cur;
		}
		cur = cur->next;
	}
//	printf("VALUE = %d\n", value);
//	printf("TEMP = %d\n", temp_a.value);
//	printf("step = %d rr = %d, rrr = %d, rr_rrr = %d, rrr_rr = %d\n",step, temp_rr, temp_rrr, temp_rr_rrr, temp_rrr_rr);
	if (temp_rr < temp_rrr && temp_rr <= temp_rr_rrr && temp_rr <= temp_rrr_rr)
		while (temp_rr-->0)
			ft_rr(stack_a, stack_b);
	else if (temp_rrr <= temp_rr && temp_rrr <= temp_rr_rrr && temp_rrr <= temp_rrr_rr )
		while (temp_rrr-->0)
			ft_rrr(stack_a, stack_b);
	else if(temp_rr_rrr <= temp_rr && temp_rr_rrr <= temp_rrr && temp_rr_rrr <= temp_rrr_rr)
	{
		while (temp_a.rr-->0)
		{
			ft_ra(stack_a, 1);
		}
		while (temp_b.rrr-->0)
			ft_rrb(stack_b,1);
	}
	else if (temp_rrr_rr <= temp_rr && temp_rrr_rr <= temp_rrr && temp_rrr_rr <= temp_rr_rrr){
		while (temp_a.rrr-->0)
		{
			ft_rra(stack_a, 1);
		}
		while (temp_b.rr-->0)
			ft_rb(stack_b,1);
	}
	ft_pa(stack_a, stack_b);
	ft_update_rr_rrr(stack_a, stack_b);

	return (value);
}

void run_solving(t_stack **stack_a, t_stack **stack_b)
{
	int value;

	ft_print_stack(*stack_a, *stack_b);
	while (*stack_b)
	{
		value = find_optimal_value(stack_a, stack_b);
//		ft_print_stack(*stack_a, *stack_b);
	}
}


void solve(t_stack **stack_a, t_stack **stack_b, int min, int m)
{
	t_stack *cur;
	int found_max;
	int max;
	t_stack *value;

	max = 0;
	cur = *stack_a;
	int k = 0;
	while (cur)
	{
//		found_max = find_max_to_remain_in_a(stack_a, cur, 0);
		found_max = find_max_to_remain_in_a2(stack_a, *stack_a,cur->value, &k);
		found_max += find_max_to_remain_in_a2_help(stack_a, *stack_a,cur->value, &k);
		k = 0;
		if (found_max > max)
		{
			value = cur;
			max = found_max;
		}
		cur = cur->next;
	}
	k = 0;
	find_max_to_remain_in_a_mark(stack_a, *stack_a, value->value, &k);
	find_max_to_remain_in_a_mark_help(stack_a, *stack_a, value->value, &k);
//	ft_print_stack(*stack_a, *stack_b);
	ft_move_from_a_to_b(stack_a, stack_b);
	ft_update_rr_rrr_a(stack_a, ft_stack_size(*stack_a));
	ft_update_rr_rrr_b(stack_b, ft_stack_size(*stack_b));
//	ft_print_stack(*stack_a, *stack_b);
	run_solving(stack_a, stack_b);

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
//				printf("COUNTER = %d\n", counter);
				return (0);
			}
			counter++;
			prev = pStack;
			pStack = pStack->next;
		}
	}
	return (1);
}

void moving_for_sort(t_stack **pStack)
{
	t_stack *cur = *pStack;
	t_stack curr;
	curr = *cur;
	while (cur)
	{
		if (cur->value < curr.value)
			curr = *cur;
		cur = cur->next;
	}
	if (curr.rr - 1 < curr.rrr)
	{
		while (curr.rr-1 > 0)
		{
			ft_ra(pStack,1);
			curr.rr--;
		}
	}
	else
	{
//		printf("RRR = %d\n",curr.rrr);
		while (curr.rrr + 1 > 0)
		{
			ft_rra(pStack, 1);
			curr.rrr--;
		}
	}
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
	moving_for_sort(&stack_a);
	printf("\n------------AFTER SORTING------------\n");
//	ft_print_stack(stack_a, stack_b);
	if (is_sorted(stack_a))
		printf("--------------SORTED--------------\n");
	printf("ans = %d", g_ans);


	return 0;
}

//8 14 4 12 5 10 1 15 2 11 7 13 3 6 9