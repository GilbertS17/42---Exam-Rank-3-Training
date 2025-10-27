/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsahyoun <gsahyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:00:16 by gsahyoun          #+#    #+#             */
/*   Updated: 2025/10/21 11:19:56 by gsahyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;		// Stores leftover text between calls
	char		*buffer;			// Temporary buffer for reading
	char		*line;				// Line to return
	int			bytes_read;			// Result from read()

	// 1. Validation
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// 2. Initialize remainder (if first call)
	if (!remainder)
		remainder = ft_calloc(1, 1);

	// 3. Allocate reading buffer
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_join_and_free(remainder, buffer); // Join buffer + remainder
		if (ft_strchr(remainder, '\n')) // Stop if newline found
			break ;
	}
	free(buffer);

	if (!remainder || !remainder[0])
		return (NULL);

	// 4. Extract one line from remainder
	int i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	for (int j = 0; j < i; j++)
		line[j] = remainder[j];
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';

	// 5. Save remainder (text after '\n') into new remainder
	int start = 0;
	while (remainder[start] && remainder[start] != '\n')
		start++;
	if (!remainder[start]) // No remainder left
	{
		free(remainder);
		remainder = NULL;
		return (line);
	}

	char *new_remainder = ft_calloc(ft_strlen(remainder) - start, sizeof(char));
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}

	int k = 0;
	while (remainder[++start])
		new_remainder[k++] = remainder[start];
	new_remainder[k] = '\0';

	free(remainder);
	remainder = new_remainder;

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
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
