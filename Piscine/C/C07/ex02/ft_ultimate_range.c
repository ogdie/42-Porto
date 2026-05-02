/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:59:02 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/08 19:52:23 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//#include <stdio.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	*temp;
	int	i;

	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	temp = malloc(sizeof(int) * (max - min));
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
int	main(void)
{
	int	min = 25;
	int	max = 30;
	int	*arr;
	int	size;
	int	i;

	size = ft_ultimate_range(&arr, min, max);
	printf("Tamanho retornado pela funcao: %d\n", size); 
	for (i = 0; i < size; i++)
	{
		printf("%d\n", arr[i]);
	}
	free(arr);
	return (0);
}*/
