/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:18:03 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/03 19:31:08 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	c;

	i = 0;
	c = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[c] != '\0' && c < nb)
	{
		dest[i] = src[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
   
  	char	src[50] = "Invicta";
  	char	dest[50]= "Cidade ";
	unsigned int	nb = 5;
     
	printf("Source string : %s\n", src);
	printf("Destination string : %s\n", dest);
	ft_strncat(dest, src, nb);
	printf("Result : %s\n", dest);
	return (0);
}*/
