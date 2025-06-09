/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/06/09 17:26:47 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_file(int fd, char *save)
{
	char	*buffer;
	ssize_t	read_bytes;

	if (!save)
	{
		save = ft_strdup("");
		if (!save)
			return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(save), NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(save), NULL);
		buffer[read_bytes] = '\0';
		save = ft_strjoin(save, buffer);
		if (!save)
			return (free(buffer), NULL);
	}
	return (free(buffer), save);
}

static char	*ft_get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = ft_substr(save, 0, i);
	return (line);
}

static char	*ft_save_remainder(char *save)
{
	int		i;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	i++;
	new_save = ft_substr(save, i, ft_strlen(save) - i);
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save_remainder(save);
	return (line);
}
