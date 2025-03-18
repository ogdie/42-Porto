/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:50 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/08 18:09:03 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	unsigned int	i;

	i = 0;
	if (nb <= 0)
	{
		return (0);
	}
	while ((i * i) < (unsigned int)nb)
	{
		i++;
	}
	if (i * i == (unsigned int)nb)
	{
		return (i);
	}
	else
	{
		return (0);
	}
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d \n", ft_sqrt(-1));
	printf("%d \n", ft_sqrt(0));
	printf("%d \n", ft_sqrt(81));
	printf("%d \n", ft_sqrt(25));	
}*/
