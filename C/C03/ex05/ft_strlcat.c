/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:37:06 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/03 19:46:39 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(dest);
	if (size <= i)
	{
		return (size + ft_strlen(src));
	}
	j = 0;
	while (src[j] && size > i + 1)
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[j]));
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[60] = "queijo_";
	char	src[] = "com_goiabada!";
	unsigned int	n = 21;

	char	dest2[50] = "suco_";
	char	src2[] = "de_uva";
	unsigned int	n2 = 12;

	printf("Ex1: %u\n", ft_strlcat(dest, src, n));
	printf("Ex2: %u\n", ft_strlcat(dest2, src2, n2));
	return (0);
}*/
