#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
int g_ans;

typedef struct s_stack
{
				int value;
				int order;
				int flag;
				struct s_stack * next;
}				t_stack;
typedef struct s_flags
{
				int	next;
				int mid;
				int max;
}				t_flags;

t_stack	*ft_new(int value, int order, int flag);
int		ft_add_back(t_stack **stack, t_stack *new, int *max, int *min);
void	ft_free_stack(t_stack **stack);
int		ft_stack_size(t_stack *stack);
int		ft_atoi(const char *str);
void	ft_swap(int *a, int *b);

void	ft_sa(t_stack **stack, int bln);
void	ft_sb(t_stack **stack, int bln);
void	ft_ss(t_stack **stack_a, t_stack **stack_b);
void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void	ft_pb(t_stack **stack_a, t_stack **stack_b);
void	ft_ra(t_stack **stack, int bln);
void	ft_rb(t_stack **stack, int bln);
void	ft_rr(t_stack **stack_a, t_stack **stack_b);
void	ft_rra(t_stack **stack, int bln);
void	ft_rrb(t_stack **stack, int bln);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b);
#endif
