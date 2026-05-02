/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:15:04 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/01 20:09:14 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_atoi(char *str)
{
	int	i;
	int	sinal;
	int	conversao;

	i = 0;
	sinal = 1;
	conversao = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sinal *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		conversao = (conversao * 10) + (str[i] - '0');
		i++;
	}
	return (conversao * sinal);
}
/*
int	main(void)
{
	printf("%d\n", ft_atoi("---+--+1234ab567"));
}*/
