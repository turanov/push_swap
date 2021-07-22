#include "get_next_line.h"
size_t	ft_getlen (const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_getjoin(char *s1, char *s2, size_t n)
{
	size_t	l1;
	char	*ans;
	size_t	i;

	i = 0;
	if (!s1)
		l1 = 0;
	else
		l1 = ft_getlen(s1);
	ans = malloc(l1 + n + 1);
	if (!ans)
		return (0);
	while (i < l1 && s1[i] != '\0')
	{
		ans[i] = s1[i];
		i++;
	}
	while (n-- && *s2 != '\0')
		ans[i++] = *s2++;
	ans[i] = '\0';
	free(s1);
	return (ans);
}

char	*ft_getdup( char *str)
{
	int		n;
	int		i;
	char	*ans;

	i = 0;
	n = ft_getlen(str);
	ans = (char *)malloc(n + 1);
	if (!ans)
		return (0);
	while (i < n)
	{
		ans[i] = str[i];
		i++;
	}	
	ans[i] = '\0';
	return (ans);
}
