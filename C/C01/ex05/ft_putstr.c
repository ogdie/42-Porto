/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:27:46 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/25 14:38:29 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		write (1, &str[index], 1);
		index++;
	}
}
/*
int	main(void)
{
	char	str[10];

	str[0] = 'D';
	str[1] = 'e';
	str[2] = 'v';
	str[3] = 'e';
	str[4] = 'l';
	str[5] = 'o';
	str[6] = 'p';
	str[7] = 'e';
	str[8] = 'r';
	ft_putstr(&str[0]);
	write(1, "\n", 1);
	return (0);
}*/
