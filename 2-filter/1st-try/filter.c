#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 1024

int start_with( char *haystack, char *needle)
{
    int j = 0;

    while (needle[j] && haystack[j] == needle[j])
        j++;
    if (needle[j] == '\0')
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2 || !argv[1][0])
    {
        printf("Error: invalid arguments\n");
        return 1;
    }
    char *s = argv[1];
    char buffer[BUFFER_SIZE];
    int bytes_read;
    int len = strlen(s);

    while ((bytes_read = read(0, buffer, BUFFER_SIZE)))
    {
        buffer[bytes_read] = '\0';
        for (int i = 0; i < bytes_read;)
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