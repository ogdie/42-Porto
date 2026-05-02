/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:30:22 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/21 19:02:45 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	unsigned char	*p = ft_calloc(5, 5);
	size_t	i = 0;

	while (i < 25)
	{
		printf("%d\n", p[i]);
		i++;
	}
}*/
