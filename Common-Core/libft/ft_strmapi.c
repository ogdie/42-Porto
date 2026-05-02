/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:11:28 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 15:53:34 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	to_alt_case(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c - 32);
	return (c);
}

#include <stdio.h>
int	main(void)
{
	char	str[] = "diego";
	char	*res = ft_strmapi(str, to_alt_case);

	printf("%s\n", res);
	return (0);
}*/
