#include "get_next_line.h"

int ft_strlen(char *s)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

int ft_strchr(const char *s, char c)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1 || !s2)
        return NULL;
    
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    
    if (!result)
        return NULL;
    
    int i = 0, j = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        result[i] = s2[j];
        i++;
        j++;
    }
    result[i] = '\0';
    return result;
}

static char	*extract_line(char *storage)
{
	int		i = 0;
	char	*line;

	if (!storage || !storage[0])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = storage[j];
	line[i] = '\0';
	return (line);
}

static char	*remove_extracted_line(char *storage)
{
	int		i = 0;
	int		j = 0;
	int		len = ft_strlen(storage);
	char	*new_storage;

	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	i++; // skip '\n'
	new_storage = malloc(len - i + 1);
	if (!new_storage)
		return (NULL);
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

/*------------------ Main Function ------------------*/

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(storage);
			storage = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		if (bytes > 0)
			storage = ft_strjoin(storage, buffer);
	}

	line = extract_line(storage);
	storage = remove_extracted_line(storage);
	return (line);
}

#include <fcntl.h>     // for open()
#include <stdio.h>     // for printf()
#include <stdlib.h>
int	main(void)
{
	int		fd;
	char	*line;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
