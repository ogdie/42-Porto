/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:43:28 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/07 23:20:46 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	len;
	int	*ptr;
	int	i;

	if (min >= max)
	{
		return (NULL);
	}
	len = max - min;
	ptr = malloc(sizeof(int) * (len));
	if (ptr == 0)
	{
		return (NULL);
	}
	i = 0;
	while (min < max)
	{
		ptr[i] = min;
		min++;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	int	min;
	int	max;
	int	*range;
	int	i;

	min = 25;
	max = 30;
	range = ft_range(min, max);
	if (range)
	{
		for (i = 0; i < max - min; i++)
		{
			printf("%d\n", range[i]);
		}
		free(range);
	}
	return (0);
}*/
