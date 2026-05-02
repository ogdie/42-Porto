/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:57:39 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/02 16:54:30 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_sqrt(int nb)
{
	unsigned int	i;

	i = 0;
	if (nb <= 0)
	{
		return (0);
	}
	while ((i * i) < (unsigned int)nb)
	{
		i++;
	}
	if (i * i == (unsigned int)nb)
	{
		return (i);
	}
	else
	{
		return (0);
	}
}
/*
int	main(void)
{
	printf("%d\n", ft_sqrt(-1));
	printf("%d\n", ft_sqrt(0));
	printf("%d\n", ft_sqrt(81));
	printf("%d\n", ft_sqrt(25));
}*/
