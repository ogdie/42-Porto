/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <dmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:42:20 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/10 18:57:19 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	signal;
	int	conv;

	signal = 1;
	conv = 0;
	while (*str == '\t' || *str == '\f' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == ' ')
	{
		str++;
	}
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			signal *= -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		conv = (*str - '0') + (conv * 10);
		str++;
	}
	return (conv * signal);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_atoi("---+--+1234ab567"));
}*/
