/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:28:22 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/08 17:09:02 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_iterative_power(-5, 5));
	printf("%d\n", ft_iterative_power(4, 2));
	printf("%d\n", ft_iterative_power(0, -1));
}*/
