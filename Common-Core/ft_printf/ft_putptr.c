/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:07 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/02 21:03:59 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long	addr;
	int				count;
	int				tmp;

	if (!ptr)
		return (write(1, "(nil)", 5));
	addr = (unsigned long)ptr;
	count = write(1, "0x", 2);
	if (count < 0)
		return (-1);
	tmp = ft_puthex(addr, 'x');
	if (tmp < 0)
		return (-1);
	return (count + tmp);
}
