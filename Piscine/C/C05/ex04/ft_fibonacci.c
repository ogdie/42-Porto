/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:04:45 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/02 15:19:31 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

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
int	main(void)
{
	printf("%d\n", ft_fibonacci(24));
	printf("%d\n", ft_fibonacci(7));
	printf("%d\n", ft_fibonacci(-15));
}*/
