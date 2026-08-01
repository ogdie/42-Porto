/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:45:12 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/02 20:45:03 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n)
{
	int	count;
	int	tmp;

	count = 0;
	if (n >= 10)
	{
		tmp = ft_putunsigned(n / 10);
		if (tmp < 0)
			return (-1);
		count += tmp;
	}
	tmp = ft_putchar((n % 10) + '0');
	if (tmp < 0)
		return (-1);
	count += tmp;
	return (count);
}
