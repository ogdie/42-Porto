/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:53:52 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/09 15:26:49 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format && format[i])
	{
		if (format[i] == '%' && format[++i])
			count += ft_format(format[i], args);
		else if (format[i])
			count += ft_putchar(format[i]);
		else
			break ;
		i++;
	}
	va_end(args);
	return (count);
}
