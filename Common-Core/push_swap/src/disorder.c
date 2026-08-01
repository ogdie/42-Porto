/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:15:07 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:06:27 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *stack)
{
	int		i;
	int		j;
	double	mistakes;
	double	total;

	if (stack->size < 2)
		return (0.0);
	i = -1;
	mistakes = 0.0;
	total = 0.0;
	while (++i < stack->size)
	{
		j = i;
		while (++j < stack->size)
		{
			total += 1.0;
			if (stack->data[i] > stack->data[j])
				mistakes += 1.0;
		}
	}
	return (mistakes / total);
}
