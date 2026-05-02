/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:50:36 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/04 14:00:06 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_comb2(void)
{
	int	a;
	int	b;
	char	c;

	a = 0;
	while (a <= 98)
	{
		b = a + 1;
		while (b <= 99)
		{
			c = (a / 10) + '0';
			write(1, &c, 1);
			c = (a % 10) + '0';
			write(1, &c, 1);
			write(1, " ", 1);
			c = (b / 10) + '0';
			write(1, &c, 1);
			c = (b % 10) + '0';
			write(1, &c, 1);
			if (!(a == 98 && b == 99))
			{
				write(1, ", ", 1);
			}
			b++;
		}
		a++;
	}
}

int	main(void)
{
	ft_print_comb2();
}
