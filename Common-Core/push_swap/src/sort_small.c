/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:11:09 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:11:11 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	pos_of_min(t_stack *stack)
{
	int	i;
	int	pos;

	i = 1;
	pos = 0;
	while (i < stack->size)
	{
		if (stack->data[i] < stack->data[pos])
			pos = i;
		i++;
	}
	return (pos);
}

static void	move_min_to_top(t_ctx *ctx)
{
	int	pos;

	pos = pos_of_min(&ctx->a);
	if (pos <= ctx->a.size / 2)
	{
		while (pos-- > 0)
			op_ra(ctx, 1);
	}
	else
	{
		pos = ctx->a.size - pos;
		while (pos-- > 0)
			op_rra(ctx, 1);
	}
}

static void	sort_three(t_ctx *ctx)
{
	int	a;
	int	b;
	int	c;

	a = ctx->a.data[0];
	b = ctx->a.data[1];
	c = ctx->a.data[2];
	if (a > b && b < c && a < c)
		op_sa(ctx, 1);
	else if (a > b && b > c)
	{
		op_sa(ctx, 1);
		op_rra(ctx, 1);
	}
	else if (a > b && a > c)
		op_ra(ctx, 1);
	else if (a < b && b > c && a < c)
	{
		op_sa(ctx, 1);
		op_ra(ctx, 1);
	}
	else if (a < b && b > c && a > c)
		op_rra(ctx, 1);
}

void	sort_small(t_ctx *ctx)
{
	if (is_sorted(&ctx->a))
		return ;
	if (ctx->a.size == 2)
		op_sa(ctx, 1);
	else if (ctx->a.size == 3)
		sort_three(ctx);
	else
	{
		while (ctx->a.size > 3)
		{
			move_min_to_top(ctx);
			op_pb(ctx, 1);
		}
		sort_three(ctx);
		while (ctx->b.size > 0)
			op_pa(ctx, 1);
	}
}
