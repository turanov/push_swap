#include <printf.h>
#include "get_next_line.h"

static int	get_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

static int	fun(const int fd, char **line, char *buffer, char **prev_str)
{
	int		fdx;
	int		index;

	fdx = read(fd, buffer, BUFFER_SIZE);
	while (fdx > 0)
	{
		buffer[fdx] = '\0';
		index = get_index(buffer);
		*line = ft_getjoin(*line, buffer, index);
		if (index != (int)ft_getlen(buffer))
		{
			*prev_str = ft_getdup(buffer + index + 1);
			return (1);
		}
		fdx = read(fd, buffer, BUFFER_SIZE);
	}
	if (fdx == 0 || (fdx == -1 && !(*prev_str)))
		free(*prev_str);
	return (fdx);
}

static int	solve(const int fd, char **line, char **prev_str)
{
	int		index;
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	if (*prev_str != NULL)
	{
		index = get_index(*prev_str);
		*line = ft_getjoin(*line, *prev_str, index);
		if (index != (int)ft_getlen(*prev_str))
		{
			temp = *prev_str;
			*prev_str = ft_getdup(*prev_str + index + 1);
			free(temp);
			return (1);
		}
		free(*prev_str);
		*prev_str = NULL;
	}
	return (fun(fd, line, buffer, prev_str));
}

int	get_next_line(const int fd, char **line)
{
	int			fdx;
	static char	*prev_str = NULL;

	if (BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	*line = 0;
	fdx = solve(fd, line, &prev_str);
	if (fdx == 0 && !(*line))
	{
		*line = malloc(1);
		*line[0] = '\0';
		if (prev_str)
			free(prev_str);
	}
	return (fdx);
}
