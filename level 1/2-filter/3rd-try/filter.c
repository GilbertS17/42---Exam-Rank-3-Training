#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 1024

int start_with(char *haystack, char *needle)
{
	int i = 0;
	while (needle[i] && haystack[i] == needle[i])
		i++;
	return (needle[i] == '\0');
}

int main (int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (perror("Error"), 1);
	char *str = argv[1];
	char buffer[BUFFER_SIZE];
	int len = strlen(str);
	int bytes;
	while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)))
	{
		buffer[bytes] = '\0';
		for (int i = 0; i < bytes;)
		{
			if (start_with(&buffer[i], str))
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
	if (bytes < 0)
	{
		perror("Error\n");
		return 1;
	}
	return 0;
}