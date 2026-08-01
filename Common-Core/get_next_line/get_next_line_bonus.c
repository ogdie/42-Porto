/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:30:40 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/23 16:30:42 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	gnl_grow(t_gnl *gnl, size_t need)
{
	char	*new_stash;
	size_t	i;
	size_t	new_cap;

	if (gnl->cap >= need)
		return (1);
	new_cap = gnl->cap;
	if (new_cap < 64)
		new_cap = 64;
	while (new_cap < need)
		new_cap *= 2;
	new_stash = ft_malloc_zero(new_cap + 1, sizeof(char));
	if (!new_stash)
		return (0);
	i = 0;
	while (i++ < gnl->len)
		new_stash[i - 1] = gnl->stash[i - 1];
	free(gnl->stash);
	gnl->stash = new_stash;
	gnl->cap = new_cap;
	return (1);
}

static int	gnl_append(t_gnl *gnl, char *buffer, ssize_t bytes)
{
	ssize_t	i;

	if (!gnl_grow(gnl, gnl->len + bytes))
		return (0);
	i = 0;
	while (i < bytes)
	{
		gnl->stash[gnl->len + i] = buffer[i];
		i++;
	}
	gnl->len += bytes;
	gnl->stash[gnl->len] = '\0';
	return (1);
}

static int	gnl_read_to_stash(int fd, t_gnl *gnl)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (0);
	bytes = 1;
	while (bytes > 0 && !gnl_has_newline(gnl->stash, gnl->len))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		if (bytes > 0 && !gnl_append(gnl, buffer, bytes))
		{
			free(buffer);
			return (0);
		}
	}
	free(buffer);
	return (bytes >= 0);
}

static char	*gnl_make_line(t_gnl *gnl)
{
	char	*line;
	size_t	i;
	size_t	used;

	used = gnl_line_len(gnl->stash, gnl->len);
	if (used == 0)
		return (NULL);
	line = ft_malloc_zero(used + 1, sizeof(char));
	if (!line)
		return (gnl_clear(gnl), NULL);
	i = 0;
	while (i < used)
	{
		line[i] = gnl->stash[i];
		i++;
	}
	gnl_shift(gnl, used);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl[OPEN_MAX];
	char			*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!gnl_read_to_stash(fd, &gnl[fd]))
	{
		gnl_clear(&gnl[fd]);
		return (NULL);
	}
	line = gnl_make_line(&gnl[fd]);
	return (line);
}
