/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 13:43:49 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 15:35:51 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_sqrt_ceil(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}
