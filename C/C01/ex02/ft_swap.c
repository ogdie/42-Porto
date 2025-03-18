/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:31:58 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/24 21:44:03 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_swap(int *a, int *b)
{
	int	swp;

	swp = *a;
	*a = *b;
	*b = swp;
}
/*
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(void)
{
	int	*a = 0;
	int 	*b = 0;
	int	firstNumber;
	int	secondNumber;

	firstNumber = 4;
	secondNumber = 2;
	a = &firstNumber;
	b = &secondNumber;
	ft_putchar(*a + '0');
	ft_putchar(' ');
	ft_putchar(*b + '0');
	ft_swap(a, b);
	ft_putchar('\n');
	ft_putchar(*a + '0');
	ft_putchar(' ');
	ft_putchar(*b + '0');
	ft_putchar('\n');
	return (0);
}*/
