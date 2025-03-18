/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:12:20 by dmenezes          #+#    #+#             */
/*   Updated: 2025/03/09 13:52:56 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	c;

	i = ac - 1;
	if (ac > 1)
	{
		while (i > 0)
		{
			c = 0;
			while (av[i][c] != '\0')
			{
				write(1, &av[i][c], 1);
				c++;
			}
			write(1, "\n", 1);
			i--;
		}
	}
	return (0);
}
