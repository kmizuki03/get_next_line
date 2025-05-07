/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:38:42 by kato              #+#    #+#             */
/*   Updated: 2025/05/07 17:34:25 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(int fd, char *stored)
{
	static ssize_t	bytes_read = 0;
	char			*buffer;
	char			*temp;

	if (stored == NULL)
		stored = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr(stored, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stored, buffer);
		free(stored);
		stored = temp;
		if (stored == NULL)
			break ;
	}
	free(buffer);
	if (bytes_read == -1)
		return (free(stored), NULL);
	return (stored);
}

static char	*extract_line(char *stored)
{
	char	*line;
	size_t	len;

	len = 0;
	if (!stored || stored[0] == '\0')
		return (NULL);
	while (stored[len] && stored[len] != '\n')
		len++;
	if (stored[len] == '\n')
		line = malloc(len + 2);
	else
		line = malloc(len + 1);
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
	new_stored = malloc(ft_strlen(stored) - i);
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
	static char	*stored[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stored[fd] = read_and_store(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = extract_line(stored[fd]);
	if (!line)
	{
		free(stored[fd]);
		stored[fd] = NULL;
		return (NULL);
	}
	stored[fd] = update_stored(stored[fd]);
	return (line);
}
