/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:31:04 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/23 16:31:06 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_has_newline(const char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (s && i < len)
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	gnl_line_len(const char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (s && i < len)
	{
		i++;
		if (s[i - 1] == '\n')
			return (i);
	}
	return (i);
}

void	gnl_shift(t_gnl *gnl, size_t used)
{
	size_t	i;

	if (used >= gnl->len)
	{
		gnl_clear(gnl);
		return ;
	}
	i = 0;
	while (used + i < gnl->len)
	{
		gnl->stash[i] = gnl->stash[used + i];
		i++;
	}
	gnl->len = i;
	gnl->stash[i] = '\0';
}

void	gnl_clear(t_gnl *gnl)
{
	free(gnl->stash);
	gnl->stash = NULL;
	gnl->len = 0;
	gnl->cap = 0;
}

void	*ft_malloc_zero(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			total;

	if (size && count > ((size_t)-1 / size))
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
