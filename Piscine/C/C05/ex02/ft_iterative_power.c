/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:54:31 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/02 14:03:05 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_iterative_power(int nb, int power)
{
	int	b;

	b = nb;
	if (power < 0)
	{
		return (0);
	}
	else if (power == 0)
	{
		return (1);
	}
	while (power > 1)
	{
		b *= nb;
		power--;
	}
	return (b);
}
/*
int	main(void)
{
	printf("%d\n", ft_iterative_power(-5, 5));
	printf("%d\n", ft_iterative_power(4, 2));
	printf("%d\n", ft_iterative_power(0, -1));
}*/
