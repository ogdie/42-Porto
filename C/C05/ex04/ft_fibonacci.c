/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:52:50 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/08 18:04:26 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fibonacci(int index)
{
	int	b;

	if (index == 0)
	{
		return (0);
	}
	else if (index == 1)
	{
		return (1);
	}
	else if (index > 1)
	{
		b = ft_fibonacci(index - 1) + ft_fibonacci(index - 2);
		return (b);
	}
	else
	{
		return (-1);
	}
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_fibonacci(24));
	printf("%d\n", ft_fibonacci(7));
	printf("%d\n", ft_fibonacci(-15));
}*/
