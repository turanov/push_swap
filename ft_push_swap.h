#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
				int content;
				struct s_stack * next;
}				t_stack;
t_stack *ft_new(int content);
int	ft_add_back(t_stack **stack, t_stack *new, int *max, int *min);
void	ft_free_stack(t_stack **stack);
int	ft_atoi(const char *str);

void ft_sa_sb(t_stack **stack);
void ft_ss(t_stack **stack_a, t_stack **stack_b);
void ft_pa_pb(t_stack **stack_a, t_stack **stack_b);
void ft_ra_rb(t_stack **stack);
void ft_rra_rrb(t_stack **stack);
void ft_rrr(t_stack **stack_a, t_stack **stack_b);
#endif
