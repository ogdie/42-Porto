/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:55:44 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/25 16:55:47 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
    char str1[] = "123456";
    char str2[] = "123456";

    ft_memmove(str1 + 2, str1, 4);
    printf("d > s  : %s\n", str1);

    ft_memmove(str2, str2 + 2, 4);
    printf("d < s  : %s\n", str2);

    return 0;
}*/
