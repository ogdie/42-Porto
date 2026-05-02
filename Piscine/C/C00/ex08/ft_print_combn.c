/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:14:04 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/12 20:23:48 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_comb(int *tab, int n)
{
	int 	i;

	i = 0;
	while (i < n )
	{
		ft_putchar(tab[i] + '0');
		i++;
	}
	if (tab[0] != 10 - n)
	{
		ft_putchar(',');
		ft_putchar(' ');
	}
}

void	generate(int *tab, int index, int n)
{
	int	i;

	if (index == n)
	{
		print_comb(tab, n);
		return;
	}
	if (index == 0)
	{
		i = 0;
	}
	else
	{
		i = tab[index - 1] + 1;
	}
	while (i <= 10 - (n - index))
	{
		tab[index] = i;
		generate(tab, index + 1, n);
		i++;
	}
}

void	ft_print_combn(int n)
{
	int	 tab[10];

	if (n > 0 && n < 10)
	{
		generate(tab, 0, n);
	}	
}

int	main(void)
{
	ft_print_combn(2);
	write(1, "\n", 1);	
}
