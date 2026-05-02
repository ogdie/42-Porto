/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:04:02 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/25 17:04:05 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	if (size <= i)
		return (size + ft_strlen(src));
	j = 0;
	while (src[j] && i + j < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[] = "Diego ";
	char	src[] = "dev";

	printf("%zu\n", ft_strlcat(dest, src, 7));
	printf("%s\n", dest);
}*/
