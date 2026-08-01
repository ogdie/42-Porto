/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:09:17 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:09:20 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	medium_has_value_until(t_stack *stack, int max)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->data[i] <= max)
			return (1);
		i++;
	}
	return (0);
}

void	push_chunk(t_ctx *ctx, int chunk_max, int chunk_size)
{
	while (medium_has_value_until(&ctx->a, chunk_max))
	{
		if (ctx->a.data[0] <= chunk_max)
		{
			op_pb(ctx, 1);
			if (ctx->b.size > 1
				&& ctx->b.data[0] < chunk_max - chunk_size / 2)
				op_rb(ctx, 1);
		}
		else
			op_ra(ctx, 1);
	}
}

void	push_all_chunks(t_ctx *ctx, int size, int chunk_size)
{
	int	chunk_max;

	chunk_max = chunk_size - 1;
	while (ctx->a.size > 0)
	{
		if (chunk_max >= size)
			chunk_max = size - 1;
		push_chunk(ctx, chunk_max, chunk_size);
		chunk_max += chunk_size;
	}
}

void	pull_b_to_a(t_ctx *ctx)
{
	int	best_pb;
	int	best_ta;

	while (ctx->b.size > 0)
	{
		simple_find_pa(ctx, &best_pb, &best_ta);
		simple_move_tops(ctx, best_ta, best_pb);
		op_pa(ctx, 1);
	}
}

void	sort_medium(t_ctx *ctx)
{
	int	size;
	int	chunk_size;

	if (ctx->a.size <= 5)
	{
		sort_small(ctx);
		return ;
	}
	size = ctx->a.size;
	chunk_size = ft_sqrt_ceil(size) * 3;
	push_all_chunks(ctx, size, chunk_size);
	pull_b_to_a(ctx);
	rotate_to_min(ctx);
}
