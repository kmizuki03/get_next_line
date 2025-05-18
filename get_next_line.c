/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:26:00 by kmizuki03         #+#    #+#             */
/*   Updated: 2025/05/18 17:45:03 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **save)
{
	char	*line;
	char	*temp;
	size_t	i;

	if (!(*save) || !(**save))
		return (NULL);
	i = 0;
	while ((*save)[i] && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		line = ft_substr(*save, 0, i + 1);
	else
		line = ft_substr(*save, 0, i);
	if (!line)
		return (free(*save), *save = NULL, NULL);
	if ((*save)[i] == '\n')
		i++;
	temp = ft_strdup(*save + i);
	if (!temp)
		return (free(line), free(*save), *save = NULL, NULL);
	free(*save);
	*save = temp;
	return (line);
}

static char	*read_buffer(int fd, char *buf, char **save)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && (!*save || !ft_strchr(*save, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*save), *save = NULL, NULL);
		buf[bytes_read] = '\0';
		if (!*save)
		{
			*save = ft_strdup("");
			if (!*save)
				return (NULL);
		}
		temp = ft_strjoin(*save, buf);
		free(*save);
		*save = temp;
		if (!*save)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (*save);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (!read_buffer(fd, buf, &save[fd]))
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	line = extract_line(&save[fd]);
	if (line && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
