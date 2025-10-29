#include "get_next_line.h"

int ft_strlen (char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int ft_strchr(char *str, int c)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == (char)c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_bzero (int size, char *str)
{
    int i = size;
    while (i != 0)
    {
        str[i] = 0;
        i--;
    }
    return str;
}

char *ft_malloc (int size, int c)
{
    int str;

    str = malloc ((size + c) * sizeof(char));
    if (!str)
        return NULL;
    str = ft_bzero(size, str);
    return str;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    char *start;

    str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!str)
        return NULL;
    start = str;
    while (*s1)
        *str++ = *s1++;
    while (*s2)
        *str++ = *s2;
    *str = '\0';
    return str;
}

char *join_and_free (char *output_text, char *buffer)
{
    char *temp;

    temp = ft_strjoin(output_text, buffer);
    free(output_text);
    return temp;
}

char    *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer;
    int bytes_read;
    int line;
    char *output_text;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return NULL;
    if (!output_text)
    {
        output_text = ft_malloc(1, 1);
        if (!output_text)
            return(free(buffer), NULL);
    }
    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read (fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            free(output_text);
            remainder= NULL;
            return NULL;
        }
        buffer[bytes_read] = '\0';
        line = join_and_free(line, buffer);
        if (ft_strchr(line, '\n'))
            break;
    }
    
}