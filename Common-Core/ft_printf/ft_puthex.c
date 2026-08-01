/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:46:35 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/02 22:10:14 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long n, char format)
{
	char	*base_low;
	char	*base_up;
	int		count;
	int		tmp;

	base_low = "0123456789abcdef";
	base_up = "0123456789ABCDEF";
	count = 0;
	tmp = 0;
	if (n >= 16)
	{
		tmp = ft_puthex(n / 16, format);
		if (tmp < 0)
			return (-1);
		count += tmp;
	}
	if (format == 'x')
		tmp = ft_putchar(base_low[n % 16]);
	else
		tmp = ft_putchar(base_up[n % 16]);
	if (tmp < 0)
		return (-1);
	count += tmp;
	return (count);
}
