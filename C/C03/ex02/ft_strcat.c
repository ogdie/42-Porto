/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:47:31 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/03 19:29:00 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[c] != '\0')
	{
		dest[i + c] = (unsigned char)src[c];
		c++;
	}
	dest[i + c] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	string1[] = "Olá ";
	char	string2[15] = "Tudo bem";

	printf("%s\n", ft_strcat(string1, string2));
	return (0);
}*/
