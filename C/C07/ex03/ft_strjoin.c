/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <dmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:17:34 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/10 23:44:12 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_lenstrs(int size, char **strs, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < size)
	{
		len = len + ft_strlen(strs[i]);
		i++;
	}
	len = len + (ft_strlen(sep) * (size - 1));
	return (len);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	str = (char *)malloc(sizeof(char) * (ft_lenstrs(size, strs, sep) + 1));
	if (str == 0)
		return (0);
	temp = str;
	while (i < size)
	{
		ft_strcpy(temp, strs[i]);
		temp = temp + ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(temp, sep);
			temp = temp + ft_strlen(sep);
		}
		i++;
	}
	*temp = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int	size;
	char	*sep;
	char	*str;
	char	**strs;

	strs = (char **)malloc(sizeof(strs) * 5);
	strs[0] = "Nada";
	strs[1] = "como um dia";
	strs[2] = "apos";
	strs[3] = "o outro";
	strs[4] = "dia!";
	sep = "_";
	size = 1;
	while (size < 6)
	{
		str = ft_strjoin(size, strs, sep);
		printf("%d: %s\n", size, str);
		free(str);
		size++;
	}
	return (0);
}*/
