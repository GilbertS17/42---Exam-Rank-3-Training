#include "get_next_line.h"

static int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

static void ft_bzero(void *s, int n)
{
	unsigned char *ptr;
	ptr = s;
	while (n--)
		*ptr++ = '\0';
}

static char *ft_calloc(int nmemb, int size)
{
	char *str = malloc(size * nmemb);
	if (!str)
		return NULL;
	ft_bzero(str, nmemb * size);
	return str;
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

static char *ft_strjoin(char *s1, char *s2)
{
	char *str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	char *start = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return start;
}

static char *str_join_and_free(char *remainder, char *buffer)
{
	char *temp;
	temp = ft_strjoin(remainder, buffer);
	free(remainder);
	return temp;
}

char *get_next_line(int fd)
{
	int bytes;
	char *buffer;
	char *new_str;
	int i = 0;
	static char *remainder = NULL;

	if (!fd || BUFFER_SIZE < 0)
		return NULL;
	if (!remainder)
		remainder = ft_calloc(1, 1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(buffer);
		free(remainder);
		remainder = NULL;
		return NULL;
	}
	bytes = 1;
	while (bytes)
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
		remainder = str_join_and_free(remainder, buffer);
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
	char *output_text = malloc ((i + 2) * sizeof(char));
	if (!output_text)
		return (free(remainder), NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		output_text[i] = remainder[i++];
	if (remainder[i] != '\n')
		output_text[i++] = '\n';
	output_text[i] = '\0';
	if (!remainder[i])
	{
		free(remainder);
		remainder = NULL;
		return output_text;
	}
	char *new_text = malloc((ft_strlen(remainder) - i) + 1);
	if (!new_text)
	{
		free(remainder);
		free(output_text);
		remainder = NULL;
		return NULL;
	}
	int j = 0;
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
	printf("%s\n", get_next_line(fd));
	return 0;
}