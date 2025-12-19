#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

char *ft_strjoin(char *s1, char *s2)
{
    int i = 0, j = 0;
    char *str = malloc (strlen(s1) + strlen(s2)+ 1);
    if (!str)
        return NULL;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return str;
}

char *join_and_free(char *s1, char *s2)
{
    char *temp = ft_strjoin(s1, s2);
    free(s1);
    return temp;
}

void ft_bzero(void *str, int n)
{
    unsigned char *ptr;
    ptr = str;
    while (n--)
        *ptr++ = '\0';
}

char *ft_calloc( int nmem, int size)
{
    char *tmp = malloc (nmem * size);
    ft_bzero(tmp, nmem * size);
    return tmp;
}

int cointains(char *haystack, char *needle)
{
    int i = 0;
    while (needle[i] && haystack[i] == needle[i])
        i++;
    return (needle[i] == '\0');
}

int main (int argc, char **argv)
{
    if (argc != 2)
        return 1;
    char *s = argv[1];
    int len = strlen(s);
    char *buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer) return 1;
    char *full_input = ft_calloc(1, 1);
    int bytes = 1;
    while (bytes > 0)
    {
        bytes = read(0, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buffer);
            return 1;
        }
        buffer[bytes] = '\0';
        full_input = join_and_free(full_input, buffer);
    }
    int full_len = strlen(full_input);
    for (int i = 0; i < full_len;)
    {
        if (cointains(&full_input[i], s))
        {
            for (int j = 0; j < len; j++)
                printf("*");
            i += len;
        }
        else
        {
            printf("%c", full_input[i]);
            i++;
        }
    }
    free(buffer);
    free(full_input);
    return 0;
}