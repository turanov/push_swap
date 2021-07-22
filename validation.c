#include "ft_push_swap.h"

int	check_max_and_min(char *s, int minus)
{
	char	*str;
	int		len;

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

int	is_digits(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	validation(char *s)
{
	int	minus;

	minus = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus++;
		s++;
	}
	minus = minus % 2;
	if (is_digits(s))
		return (check_max_and_min(s, minus));
	return (0);
}

void	ft_free_splited(char **splited)
{
	int	i;

	i = 0;
	if (!*splited || !splited)
		return ;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

int	is_emtpy_flag(t_stack *pStack)
{
	while (pStack)
	{
		if (pStack->flag == 0)
			return (0);
		pStack = pStack->next;
	}
	return (1);
}
