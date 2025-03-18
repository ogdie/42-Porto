/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:45:41 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/27 17:47:04 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_is_negative(int i)
{
	if (i < 0)
		write(1, "N", 1);
	else
		write(1, "P", 1);
}
int	main(void)
{
	ft_is_negative(42);
	ft_is_negative(-42);
	ft_is_negative(0);
}
