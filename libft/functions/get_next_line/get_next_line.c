/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:31:28 by jwhitley          #+#    #+#             */
/*   Updated: 2024/07/12 16:06:38 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*leftover(char *buffer)
{
	int		i;
	int		j;
	char	*leftover;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	leftover = (char *)malloc((gnl_strlen(buffer) - i + 1) * sizeof(char));
	if (!leftover)
		return (NULL);
	i++;
	while (buffer[i])
		leftover[j++] = buffer[i++];
	leftover[j] = '\0';
	free(buffer);
	return (leftover);
}

char	*next_line(char *buffer)
{
	int		i;
	char	*result;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	result = (char *)malloc((i + 2) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*read_file(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = next_line(buffer);
	buffer = leftover(buffer);
	return (line);
}
