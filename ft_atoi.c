#include "ft_push_swap.h"

int	ft_atoi(const char *str)
{
    int ans;
    int minus;

    minus = 1;
    ans = 0;
    if (*str == '-')
    {
        str++;
        minus = -1;
    }
    while (*str)
    {
        ans = ans * 10 + (*str - 48);
        str++;
    }
    return (ans * minus);
}