/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:32:21 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/08 17:16:26 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <stdio.h>

int	main(void)

{
	printf("%d\n", ft_recursive_power(-5, 5));
	printf("%d\n", ft_recursive_power(5, 4));
	printf("%d\n", ft_recursive_power(0, -1));
	printf("%d\n", ft_recursive_power(4, 0));

}*/
