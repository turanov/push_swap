#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"

typedef struct s_stack
{
	int				value;
	int				flag;
	int				rr;
	int				rrr;
	struct s_stack	*next;
}					t_stack;

typedef struct s_temp
{
	int				rr;
	int				rrr;
	int				rr_rrr;
	int				rrr_rr;
}					t_temp;

t_stack	*ft_new(int value, int flag);
int		ft_add_front(t_stack **stack, t_stack *new);
void	ft_free_stack(t_stack **stack);
int		ft_stack_size(t_stack *stack);
void	ft_swap(int *a, int *b);

void	ft_sa(t_stack **stack, char *str);
void	ft_sb(t_stack **stack, char *str);
void	ft_ss(t_stack **stack_a, t_stack **stack_b, char *str);
void	ft_pa(t_stack **stack_a, t_stack **stack_b, char *str);
void	ft_pb(t_stack **stack_a, t_stack **stack_b, char *str);
void	ft_ra(t_stack **stack, char *str);
void	ft_rb(t_stack **stack, char *str);
void	ft_rr(t_stack **stack_a, t_stack **stack_b, char *str);
void	ft_rra(t_stack **stack, char *str);
void	ft_rrb(t_stack **stack, char *str);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b, char *str);

int		check_max_and_min(char *s, int minus);
int		is_digits(char *s);
int		validation(char *s);
void	ft_free_splited(char **splited);
int		is_emtpy_flag(t_stack *pStack);
int		find_max_to_remain_in_a2(t_stack **pStack, t_stack *cur,
			int value, int *max);
int		find_max_to_remain_in_a2_help(t_stack **pStack, t_stack *cur,
			int value, int *max);
int		find_max_to_remain_in_a_mark(t_stack **pStack, t_stack *cur,
			int value, int *max);
int		find_max_to_remain_in_a_mark_help(t_stack **pStack, t_stack *cur,
			int value, int *max);
void	ft_move_from_a_to_b(t_stack **stack_a, t_stack **stack_b);
int		find_step_a_helper(t_stack *cur, int value, int *max, t_stack *temp);
t_stack	find_step_a(t_stack **stack_a, int value, int max);
int		ft_max(int rr, int rrr);
int		ft_min(int a, int b);
int		find_min_step(t_temp temp);
void	fun_rr(t_stack **stack_a, t_stack **stack_b,
			t_stack temp_a, t_stack temp_b);
void	fun_rrr(t_stack **stack_a, t_stack **stack_b,
			t_stack temp_a, t_stack temp_b);
void	fun_rr2(t_stack **stack_a, t_stack **stack_b,
			t_stack temp_a, t_stack temp_b);
void	fun_rrr2(t_stack **stack_a, t_stack **stack_b,
			t_stack temp_a, t_stack temp_b);
t_temp	fun(t_stack a, t_stack *cur);
void	ft_update_rr_rrr_a(t_stack **stack_a, int size);
void	ft_update_rr_rrr_b(t_stack **stack_b, int size);
void	ft_update_rr_rrr(t_stack **stack_a, t_stack **stack_b);
int		fund(t_stack a, t_stack *temp_a, t_stack *temp_b, t_stack *cur);
void	find_optimal_value_help(t_stack **stack_a, t_stack **stack_b);
void	find_optimal_value(t_stack **stack_a, t_stack **stack_b,
			t_stack *cur, int min_step);
void	run_solving(t_stack **stack_a, t_stack **stack_b);
void	solve(t_stack **stack_a, t_stack **stack_b,
			t_stack *cur, t_stack *value);
void	moving_for_sort_help(t_stack **pStack, t_stack curr);
void	moving_for_sort(t_stack **pStack);
int		is_sorted(t_stack *pStack);
int		main_helper(char **splited, t_stack **stack_a);
void	ft_sort_three(t_stack **pStack);
void	sort_two(t_stack **stack);
int		find_min(t_stack **stack_a);
void	ft_sort_four(t_stack **stack_a, t_stack **stack_b);
void	ft_sort_five(t_stack **stack_a, t_stack **stack_b);

#endif
