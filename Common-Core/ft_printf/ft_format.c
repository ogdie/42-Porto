/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:54:30 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/02 20:09:49 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(char spec, va_list args)
{
	if (spec == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (spec == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (spec == 'd' || spec == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (spec == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	if (spec == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 'x'));
	if (spec == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 'X'));
	if (spec == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (spec == '%')
		return (ft_putchar('%'));
	return (0);
}
