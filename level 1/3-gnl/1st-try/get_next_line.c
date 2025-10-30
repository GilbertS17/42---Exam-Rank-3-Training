#include "get_next_line.h"

int ft_strlen(char *str)
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

void ft_bzero(void *s, int n)
{
    unsigned char *ptr;

    ptr = s;
    while (n--)
        *ptr++ = '\0';
}

char *ft_calloc(int size, int count)
{
    char *ptr;

    ptr = malloc(size * count);
    ft_bzero(ptr, size * count);
    return ptr;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    char *start;

    str = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    start = str;
    while (*s1)
        *str++ = *s1++;
    while (*s2)
        *str++ = *s2++;
    *str = '\0';
    return start;
}

char *ft_join_and_free(char *s1, char *s2)
{
    char *temp;
    
    temp = ft_strjoin(s1, s2);
    free(s1);
    return temp;
}

char    *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer;
    char *output_text;
    char *new_text;
    int bytes_read;
    int i;
    int j;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    if (!remainder)
        remainder = ft_calloc(1, 1);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        free(remainder);
        remainder = NULL;
        return NULL;
    }
    bytes_read = 1;
    while (bytes_read > 0)
    {
       bytes_read = read(fd, buffer, BUFFER_SIZE);
       if (bytes_read == -1)
       {
        free(remainder);
        free(buffer);
        remainder = NULL;
        return NULL;
       }
       buffer[bytes_read] = '\0';
       remainder = ft_join_and_free(remainder, buffer);
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
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
        i++;
    output_text = malloc((i + 2) * sizeof(char));
    if (!output_text)
        return NULL;
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
    {
        output_text[i] = remainder[i];
        i++;
    }
    if (remainder[i] != '\n')
        output_text[i++] = '\n';
    output_text[i++] = '\0';

    if (!remainder[i])
	{
		free(remainder);
		remainder = NULL;
		return (output_text);
	}
    
    new_text = ft_calloc(ft_strlen(remainder) - i + 1, sizeof(char));
    if (!new_text)
    {
        free(remainder);
		free(output_text);
        remainder = NULL;
        return NULL;
    }
    j = 0;
    while (remainder[i])
        new_text[j++] = remainder[i++];
    new_text[j] = '\0';
    free(remainder);
    remainder = new_text;
    return output_text;
}

#include <fcntl.h>
#include <stdio.h>

int main (void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        printf("Invalid file");
    char *line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    close(fd);
    return 0;
}