/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <dmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:07:06 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/10 18:16:32 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0 && nb / 10 == 0)
	{
		ft_putchar('-');
	}
	if (nb / 10 != 0)
	{
		ft_putnbr(nb / 10);
	}
	if (nb % 10 < 0)
	{
		ft_putchar((nb % 10) * -1 + '0');
	}
	else
	{
		ft_putchar((nb % 10) + '0');
	}
}
/*
int	main(void)
{
	ft_putnbr(-2147483648);
	write(1, "\n", 1);
	ft_putnbr(2147483647);
	write(1, "\n", 1);
	return (0);
}*/
