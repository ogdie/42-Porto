/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 15:40:15 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 15:41:22 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, long nb, int len)
{
	str[len] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return ;
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = get_len(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, nb, len);
	return (str);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%s\n", ft_itoa(-12352));
}*/
