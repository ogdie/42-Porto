/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:10:27 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:10:30 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_sync(t_ctx *ctx, int *ca, int *cb, int fa)
{
	while (*ca > 0 && *cb > 0)
	{
		if (fa)
			op_rr(ctx, 1);
		else
			op_rrr(ctx, 1);
		(*ca)--;
		(*cb)--;
	}
}

void	simple_move_tops(t_ctx *ctx, int pos_a, int pos_b)
{
	int	ca;
	int	cb;
	int	fa;
	int	fb;

	ca = simple_cost(pos_a, ctx->a.size, &fa);
	cb = simple_cost(pos_b, ctx->b.size, &fb);
	if (fa == fb)
		move_sync(ctx, &ca, &cb, fa);
	while (ca-- > 0)
	{
		if (fa)
			op_ra(ctx, 1);
		else
			op_rra(ctx, 1);
	}
	while (cb-- > 0)
	{
		if (fb)
			op_rb(ctx, 1);
		else
			op_rrb(ctx, 1);
	}
}

void	rotate_to_min(t_ctx *ctx)
{
	int	min_pos;
	int	i;
	int	steps;
	int	fwd;

	min_pos = 0;
	i = 1;
	while (i < ctx->a.size)
	{
		if (ctx->a.data[i] < ctx->a.data[min_pos])
			min_pos = i;
		i++;
	}
	steps = simple_cost(min_pos, ctx->a.size, &fwd);
	while (steps-- > 0)
	{
		if (fwd)
			op_ra(ctx, 1);
		else
			op_rra(ctx, 1);
	}
}

static void	phase_push_b(t_ctx *ctx)
{
	int	best_pa;
	int	best_tb;

	while (ctx->a.size > 3)
	{
		simple_find_pb(ctx, &best_pa, &best_tb);
		simple_move_tops(ctx, best_pa, best_tb);
		op_pb(ctx, 1);
	}
}

void	sort_simple(t_ctx *ctx)
{
	int	best_pb;
	int	best_ta;

	if (ctx->a.size <= 5)
	{
		sort_small(ctx);
		return ;
	}
	phase_push_b(ctx);
	sort_small(ctx);
	while (ctx->b.size > 0)
	{
		simple_find_pa(ctx, &best_pb, &best_ta);
		simple_move_tops(ctx, best_ta, best_pb);
		op_pa(ctx, 1);
	}
	rotate_to_min(ctx);
}
