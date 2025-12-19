#include "get_next_line.h"

int ft_strlen(char *str)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_bzero(void *str, int n)
{
    unsigned char *ptr;
    ptr = str;
    while (n--)
        *ptr++ = '\0';
}

int ft_strchr(char *str, char c)
{
    if (!str)
        return 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_strjoin(char *s1 ,char *s2)
{
    int i = 0, j = 0;
    char *str;

    if (!s1 || !s2)
        return NULL;

    str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!str)
        return NULL;

    while (s1[i])
        str[j++] = s1[i++];
    i = 0;
    while (s2[i])
        str[j++] = s2[i++];
    str[j] = '\0';
    return str;
}

char *join_and_free(char *s1 ,char *s2)
{
    char *tmp;
    
    tmp = ft_strjoin(s1, s2);
    free(s1);
    return tmp;
}

char *ft_calloc (int nmem, int size)
{
    char *ptr = malloc (nmem * size);
    if (!ptr)
        return NULL;
    ft_bzero(ptr, nmem * size);
    return ptr;
}

char    *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer;
    int bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    if (!remainder)
        remainder = ft_calloc(1, 1);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (free(remainder), NULL);
    bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buffer);
            free(remainder);
            remainder = NULL;
            return NULL;
        }
        buffer[bytes] = '\0';
        remainder = join_and_free(remainder, buffer);
        if (ft_strchr(remainder, '\n'))
            break;
    }
    free(buffer);
    if (!remainder || !remainder[0])
    {
        free(remainder);
        remainder = NULL;
        return NULL;
    }
    int i = 0;
    while (remainder[i] && remainder[i] != '\n')
        i++;
    char *output = ft_calloc((i + 2), sizeof(char));
    if (!output)
    {
        free(remainder);
        remainder = NULL;
        return NULL;
    }
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
    {
        output[i] = remainder[i];
        i++;
    }   
    if (remainder[i] == '\n')
        output[i] = remainder[i++];
    output[i] = '\0';
    if (!remainder[i])
    {
        free(remainder);
        remainder = NULL;
        return output;
    }
    char *new_txt = malloc((ft_strlen(remainder) - i + 1) * sizeof(char));
    if (!new_txt)
    {
        free(remainder);
        free(output);
        remainder = NULL;
        return NULL;
    }
    int j = 0;
    while (remainder[i])
        new_txt[j++] = remainder[i++];
    new_txt[j] = '\0';
    free(remainder);
    remainder = new_txt;
    return output;
}
#include <fcntl.h>
#include <stdio.h>

int main (int argc, char **argv)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return 0;
}