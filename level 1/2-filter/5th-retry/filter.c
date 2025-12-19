#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

int ft_strchr(char *haystack, char *needle)
{
    int i = 0;
    while (needle[i] && haystack[i] == needle[i])
        i++;
    return (needle[i] == '\0');
}

static char *ft_strjoin(char *s1, char *s2)
{
    char *start, *str;
    str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    start = str;
    while (*s1)
        *str++ = *s1++;
    while (*s2)
        *str++ = *s2++;
    *str = '\0';
    return start;
}

static char *free_and_join(char *s1, char *s2)
{
    char *temp = ft_strjoin(s1, s2);
    free(s1);
    return temp;
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *s = argv[1];
    char *buffer;
    char *full_input;
    full_input = malloc(1);
    if (!full_input)
        return (write(2, "Error: malloc", 13), 1);
    full_input[0] = '\0';
    int len = strlen(s);
    buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
    {
        free(full_input);
        return (write(2, "Error: malloc", 13), 1);
    }
    int bytes = 1;
    while (bytes > 0)
    {
        bytes = read(0, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buffer);
            write(2, "Error: read", 11);
            return (1);
        }
        buffer[bytes] = '\0';
        full_input = free_and_join(full_input, buffer);
    }
    free(buffer);
    int full_len = ft_strlen(full_input);
    for (int i = 0; i < full_len;)
    {
        if (ft_strchr(&full_input[i], s))
        {
            for (int i = 0; i < len; i++)
                write(1, "*", 1);
            i += len;
        }
        else
        {
            write(1, &full_input[i], 1);
            i++;
        }
    }
    free(full_input);
    return 0;
}
