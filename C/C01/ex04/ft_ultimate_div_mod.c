/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:05:21 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/26 13:52:16 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	div;
	int	mod;

	div = *a / *b;
	mod = *a % *b;
	*a = div;
	*b = mod;
}
/*
int	main(void)
{
	int 	a;
	int	b;

	a = 7;
	b = 3;
	printf("Divisao: %d / %d", a, b);
	ft_ultimate_div_mod(&a, &b);
	printf("\nResultado da divisao: %d\n", a);
	printf("Modulo: %d \n", b);
	return (0);
}*/
