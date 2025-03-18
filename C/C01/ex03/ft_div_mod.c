/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:05:06 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/24 22:13:17 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a / b;
	*mod = a % b;
}
/*
int	main(void)
{
	int	a;
	int	b;
	int	div;
	int	mod;

	a = 42;
	b = 10;
	printf("Divisao %d / %d", a, b);
	ft_div_mod(a, b, &div, &mod);
	printf("\nResultado da divisao %d\n", div);
	printf("Modulo %d \n", mod);
	return (0);
}*/
