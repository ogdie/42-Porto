/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 20:22:54 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/21 20:23:58 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "abcdef";
	int	i = 0;
	
	ft_bzero(str, 4);
	while (i < 6)
	{
		printf("%d\n", str[i]);
		i++;
	}
}*/
