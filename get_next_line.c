/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:10:00 by kato              #+#    #+#             */
/*   Updated: 2025/05/04 20:12:17 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(int fd, char *stored)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stored, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stored = ft_strjoin(stored, buffer);
	}
	free(buffer);
	return (stored);
}

static char	*extract_line(char *stored)
{
	char	*line;
	size_t	len;

	if (!stored || *stored == '\0')
		return (NULL);
	len = 0;
	while (stored[len] && stored[len] != '\n')
		len++;
	line = malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	len = 0;
	while (stored[len] && stored[len] != '\n')
	{
		line[len] = stored[len];
		len++;
	}
	if (stored[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

static char	*update_stored(char *stored)
{
	char	*new_stored;
	size_t	i;
	size_t	j;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	new_stored = malloc((ft_strlen(stored) - i + 1) * sizeof(char));
	if (!new_stored)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		new_stored[j++] = stored[i++];
	new_stored[j] = '\0';
	free(stored);
	return (new_stored);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = read_and_store(fd, stored);
	if (!stored)
		return (NULL);
	line = extract_line(stored);
	stored = update_stored(stored);
	return (line);
}
