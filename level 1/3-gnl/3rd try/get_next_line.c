#include "get_next_line.h"

static void ft_bzero(void *str, int size)
{
	unsigned char *ptr;
	ptr = str;

	while (size--)
		*ptr++ = '\0';
}

static char *ft_calloc(int nmemb, int size)
{
	char *str = malloc ((nmemb * size) * sizeof(char));
	if (!str)
		return NULL;
	ft_bzero(str, nmemb * size);
	return str;
}

static int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;
}

static char *ft_strjoin(char *s1, char *s2)
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

static char *join_and_free(char *remainder, char *buffer)
{
	char *temp;
	temp = ft_strjoin(remainder, buffer);
	free(remainder);
	return temp;
}

int ft_strchr(char *str, char c)
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

	if (fd <= 0 || BUFFER_SIZE < 0)
		return NULL;
	if (!remainder)
		remainder = ft_calloc(1, 1);
	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(remainder);
		remainder = NULL;
		return NULL;
	}
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (fd == -1)
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
	char *output = malloc ((i + 2) * sizeof(char));
	if (!output)
	{
		free(remainder);
		remainder = NULL;
		return NULL;
	}
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		output[i++] = remainder[i];
	if (remainder[i] != '\n')
		output[i++] = '\n';
	output[i] = '\0';
	if (!ft_strchr(remainder, '\n'))
	{
		free(remainder);
		remainder = NULL;
		return output;
	}
	char *new_str = malloc((ft_strlen(remainder) - i + 1) * sizeof(char));
	if (!new_str)
	{
		free(remainder);
		remainder = NULL;
		return NULL;
	}
	int j = 0;
	while (remainder[i])
		new_str[j++] = remainder[i++];
	free(remainder);
	new_str[j] = '\0';
	return output;
}


#include <fcntl.h>
#include <stdio.h>
int main (void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return(printf("failed to open file"), 1);
	printf("%s\n", get_next_line(fd));
	close (fd);
	return 0;
}