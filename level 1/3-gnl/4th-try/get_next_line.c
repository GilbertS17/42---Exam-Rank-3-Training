#include "get_next_line.h"

static void ft_bzero(void *str, int n)
{
    unsigned char *ptr;
    ptr = str;
    while (n--)
        *ptr++ = '\0';
}

static char *ft_calloc(int nmem, int size)
{
    char *str = malloc (size * nmem);
    ft_bzero(str, nmem * size);
    return str;
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
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

static int ft_strchr(char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer;
    int bytes;

    if (!fd || BUFFER_SIZE <= 0)
        return NULL;
    if (!remainder)
        remainder = ft_calloc(1, 1);
    buffer = malloc (BUFFER_SIZE * sizeof(char));
    if (!buffer)
        return NULL;
    bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free (remainder);
            free (buffer);
            remainder = NULL;
            return NULL;
        }
        buffer[bytes] = '\0';
        remainder = free_and_join(remainder, buffer);
        if (ft_strchr(remainder, '\n'))
            break;
    }
    free(buffer);
    if (!remainder || !remainder[0])
    {
        free (remainder);
        remainder = NULL;
        return NULL;
    }
    int i = 0;
    while (remainder[i] && remainder[i] != '\n')
        i++;
    char *output = malloc ((i + 2) * sizeof(char));
    if (!output)
    {
        free (remainder);
        remainder = NULL;
        return NULL;
    }
    i = 0;
    while (remainder[i] && remainder[i] != '\n')
    {
        output[i] = remainder[i];
        i++;
    }
    if (remainder[i] != '\n')
        output[i++] = '\n';
    output[i++] = '\0';
    if (!remainder[i])
    {
        free (remainder);
        remainder = NULL;
        return output;
    }

    char *new_txt = malloc ((ft_strlen(remainder) - i + 1) * sizeof(char));
    if (!new_txt)
    {
        free (remainder);
        free (output);
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

int main (void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    line = get_next_line(fd);
    printf("%s\n" , line);
    free(line);
    line = get_next_line(fd);
    printf("%s\n" , line);
    free(line);
    line = get_next_line(fd);
    printf("%s\n" , line);
    free(line);
    return 0;
}