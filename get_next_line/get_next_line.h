#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <fcntl.h> 
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(const int fd, char **line);
size_t	ft_getlen (const char *str);
char	*ft_getjoin(char *s1, char *s2, size_t n);
char	*ft_getdup( char *str);

#endif
