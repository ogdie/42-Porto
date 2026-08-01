/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:13:34 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 15:36:01 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	init_stack(t_stack *stack, int capacity)
{
	stack->data = malloc(sizeof(int) * capacity);
	if (!stack->data && capacity > 0)
		return (0);
	stack->size = 0;
	stack->capacity = capacity;
	return (1);
}

void	free_ctx(t_ctx *ctx)
{
	free(ctx->a.data);
	free(ctx->b.data);
	ctx->a.data = NULL;
	ctx->b.data = NULL;
}

int	push_top(t_stack *stack, int value)
{
	int	i;

	if (stack->size >= stack->capacity)
		return (0);
	i = stack->size;
	while (i > 0)
	{
		stack->data[i] = stack->data[i - 1];
		i--;
	}
	stack->data[0] = value;
	stack->size++;
	return (1);
}

int	is_sorted(t_stack *stack)
{
	int	i;

	i = 0;
	while (i + 1 < stack->size)
	{
		if (stack->data[i] > stack->data[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicate(t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
			if (stack->data[i] == stack->data[j++])
				return (1);
		i++;
	}
	return (0);
}
