/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <dmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:03:40 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/10 23:39:02 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ptr = (int *)malloc(sizeof(int) * len);
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
#include <stdio.h>

int	main(void)
{
	int	min;
	int	max;
	int	*range;

	min = 25;
	max = 30;
	range = ft_range(min, max);
	if (range)
	{
		int	*p = range;
		while (min < max)
		{
			printf("%d\n", *p++);
			min++;
		}
		free(range);
	}
	return (0);
}*/
