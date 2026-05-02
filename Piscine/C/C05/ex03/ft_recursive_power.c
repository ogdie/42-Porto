/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:03:46 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/02 15:04:19 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
	{
		return (0);
	}
	else if (power == 0)
	{
		return (1);
	}
	else
	{
		return (nb * ft_recursive_power(nb, power - 1));
	}
}
/*
int	main(void)
{
	printf("%d\n", ft_recursive_power(-5, 5));
	printf("%d\n", ft_recursive_power(-5, 4));
	printf("%d\n", ft_recursive_power(0, -1));
	printf("%d\n", ft_recursive_power(4, 0));
}*/
