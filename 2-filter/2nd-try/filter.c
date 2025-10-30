#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 42

int start_with(char *haystack, char *needle)
{
    int j = 0;
    while (needle[j] && needle[j] == haystack[j])
        j++;
    if (needle[j] == '\0')
        return 1;
    else
        return 0;
}

int main (int argc, char **argv)
{
    if (argc != 2 || !argv[1][0])
    {
        printf("Error: Argument missing\n");
        return 1;
    }
    int bytes_read;
    char buffer[BUFFER_SIZE];
    char *s = argv[1];
    int len = strlen(s);
    while ((bytes_read = read(0, buffer, BUFFER_SIZE)))
    {
        buffer[bytes_read] = '\0';
        for(int i = 0; i < bytes_read;)
        {
            if (start_with(&buffer[i], s))
            {
                for (int j = 0; j < len; j++)
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
    if (bytes_read == -1)
    {
        perror("Error");
        return 1;
    }
    return 0;
}