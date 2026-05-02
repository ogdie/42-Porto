/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:29:01 by diemonte          #+#    #+#             */
/*   Updated: 2026/01/28 18:40:01 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *b;
	*b = *a;
	*a = temp;
}
/*
int	main(void)
{
	int	a;
	int	b;

	a = 2;
	b = 4;
	printf("antes: a = %d - b = %d\n", a, b);
	ft_swap(&a, &b);
	printf("depois: a = %d - b = %d\n", a, b);
}*/
