#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int	    ft_strlen(char *s);
int     ft_strchr(const char *s, char c);
char	*ft_strjoin(char *s1, char *s2);

#endif
