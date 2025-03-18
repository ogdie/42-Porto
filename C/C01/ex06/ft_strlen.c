/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:40:25 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/25 18:03:38 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	int	i;
	char	str[6];

	str[0] = 'P';
	str[1] = 'o';
	str[2] = 'r';
	str[3] = 't';
	str[4] = 'o';
	i = 0;
	i = ft_strlen(str);
	printf("Tamanho: %d \n", i);
	return (0);
}*/
