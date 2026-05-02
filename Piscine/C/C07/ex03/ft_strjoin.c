/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:01:02 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/08 18:04:54 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char	*str)
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

char	*ft_empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	return (str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	if (size == 0)
		return (ft_empty_string());
	str = malloc(sizeof(char) * (ft_lenstrs(size, strs, sep) + 1));
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
int	main(void)
{
	char	*words[] = {"Oi", "como", "vai"};
	char	*sep = " ";
	char	*result;
	int	size = 3;

	result = ft_strjoin(size, words, sep);
	if (result)
	{
		printf("resultado: %s\n", result);
		free(result);
	}
	else
	{
		printf("Erro ao criar string!\n");
	}
	return (0);
}*/
