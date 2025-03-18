/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:27:45 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/03 19:34:09 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	c;

	i = 0;
	if (to_find[0] == '\0')
	{
		return (str);
	}
	while (str[i] != '\0')
	{
		c = 0;
		while (str[i + c] != '\0' && str[i + c] == to_find[c])
		{
			if (to_find[c + 1] == '\0')
			{
				return (&str[i]);
			}
			c++;
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str[14] = "Super Dragoes";
	char	to_find[10] = "Porto";
	char	to_find2[10] = "Dra";

	printf("Ex1: substring é -> %s\n", ft_strstr(str, to_find));
	printf("Ex2: substring é -> %s\n", ft_strstr(str, to_find2));
	return (0);
}*/
