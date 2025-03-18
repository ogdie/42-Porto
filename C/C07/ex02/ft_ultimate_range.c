/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <dmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:10:46 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/10 23:39:45 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	*temp;
	int	i;

	if (min >= max)
	{
		return (0);
	}
	temp = (int *)malloc(sizeof(int) * (max - min));
	if (temp == 0)
	{
		return (-1);
	}
	i = 0;
	while (min < max)
	{
		temp[i] = min;
		min++;
		i++;
	}
	*range = temp;
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	int	**arr;
	int	*arr2;
	int	i;

	i = 0;
	arr = &arr2;
	printf("Total: %d\n", ft_ultimate_range(arr, 0, 10));
	while (i < 10)
	{
		printf("%d\n", arr2[i]);
		i++;
	}
	free(arr2);
	return (0);
}*/
