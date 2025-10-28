#include "get_next_line.h"

int ft_strlen(char *s)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

int ft_strchr(const char *s, char c)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1 || !s2)
        return NULL;
    
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    
    if (!result)
        return NULL;
    
    int i = 0, j = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        result[i] = s2[j];
        i++;
        j++;
    }
    result[i] = '\0';
    return result;
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_read = 0;
    static int buffer_pos = 0;
    char *line;
    int i = 0;
    int line_size = 1000;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    
    line = malloc(line_size);
    if (!line)
        return NULL;
    
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            
            if (buffer_read == 0)
                break;
            else if (buffer_read < 0)
            {
                free(line);
                return NULL;
            }
        }
        line[i++] = buffer[buffer_pos++];
        if (line[i - 1] == '\n')
            break;
    }
    line[i] = '\0';
    if (i == 0)
    {
        free(line);
        return NULL;
    }
    return line;
}

// #include <fcntl.h>     // for open()
// #include <stdio.h>     // for printf()
// #include <stdlib.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
