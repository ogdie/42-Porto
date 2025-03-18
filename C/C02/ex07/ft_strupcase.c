/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:04:03 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/02 13:00:26 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 97 && str[i] <= 122)
		{
			str[i] += (65 - 97);
		}
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "passei";
	char	str1[] = "DieGo";

	printf("%s\n", ft_strupcase(str));
	printf("%s\n", ft_strupcase(str1));
}*/
