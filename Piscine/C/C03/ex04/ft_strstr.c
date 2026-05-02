/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:03:36 by diemonte          #+#    #+#             */
/*   Updated: 2026/01/31 19:45:01 by diemonte         ###   ########.fr       */
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
		while ((str[i + c] != '\0') && (str[i + c] == to_find[c]))
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
	char	s1[] = "Hello 42 School";
	char	s2[] = "42";

	printf("%s\n", ft_strstr(s1, s2));
	return (0);
}*/
