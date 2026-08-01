/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:54:07 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 18:06:30 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rank_of(t_stack *stack, int pos)
{
	int	rank;
	int	j;

	rank = 0;
	j = 0;
	while (j < stack->size)
	{
		if (stack->data[j] < stack->data[pos])
			rank++;
		j++;
	}
	return (rank);
}

int	normalize_stack(t_stack *stack)
{
	int	*ranked;
	int	i;

	ranked = malloc(sizeof(int) * stack->size);
	if (!ranked && stack->size > 0)
		return (0);
	i = -1;
	while (++i < stack->size)
		ranked[i] = rank_of(stack, i);
	i = -1;
	while (++i < stack->size)
		stack->data[i] = ranked[i];
	free(ranked);
	return (1);
}
