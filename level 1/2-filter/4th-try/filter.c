#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

int ft_strchr(char *haystack, char *needle)
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
    char *buffer;
    int len = strlen(s);
    buffer = malloc (BUFFER_SIZE * sizeof(char));
    if (!buffer)
        return (write(2, "Error: malloc", 13), 1);
    int bytes;
    while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes] = '\0';
        for (int i = 0; i < BUFFER_SIZE;)
        {
            if (ft_strchr(&buffer[i], s))
            {
                for (int i = 0; i < len; i++)
                    write(1, "*", 1);
                i += len;
            }
            else
            {
                write(1, &buffer[i], 1);
                i++;
            }
        }
    }
    if (bytes < 0)
        return (write(2, "Error: read", 11), 1);
    return 0;
}