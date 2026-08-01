/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:09:36 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:09:43 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	simple_target_b(t_stack *b, int value)
{
	int	best;
	int	best_v;
	int	i;

	if (b->size == 0)
		return (0);
	best = -1;
	best_v = -2147483648;
	i = 0;
	while (i < b->size)
	{
		if (b->data[i] < value && b->data[i] > best_v)
		{
			best_v = b->data[i];
			best = i;
		}
		i++;
	}
	if (best >= 0)
		return (best);
	return (find_max_pos(b));
}

int	simple_target_a(t_stack *a, int value)
{
	int	best;
	int	best_v;
	int	i;

	if (a->size == 0)
		return (0);
	best = -1;
	best_v = 2147483647;
	i = 0;
	while (i < a->size)
	{
		if (a->data[i] >= value && a->data[i] < best_v)
		{
			best_v = a->data[i];
			best = i;
		}
		i++;
	}
	if (best >= 0)
		return (best);
	return (find_min_pos(a));
}

int	simple_cost(int pos, int sz, int *fwd)
{
	if (sz == 0 || pos == 0)
	{
		*fwd = 1;
		return (0);
	}
	if (pos <= sz / 2)
	{
		*fwd = 1;
		return (pos);
	}
	*fwd = 0;
	return (sz - pos);
}

int	simple_combined(int pa, int tb, int sa, int sb)
{
	int	ca;
	int	cb;
	int	fa;
	int	fb;

	ca = simple_cost(pa, sa, &fa);
	cb = simple_cost(tb, sb, &fb);
	if (fa == fb)
		return (get_max(ca, cb));
	return (ca + cb);
}

void	simple_find_pb(t_ctx *ctx, int *best_pa, int *best_tb)
{
	int	i;
	int	tb;
	int	cost;
	int	best;

	best = 2147483647;
	*best_pa = 0;
	*best_tb = 0;
	i = 0;
	while (i < ctx->a.size)
	{
		tb = simple_target_b(&ctx->b, ctx->a.data[i]);
		cost = simple_combined(i, tb, ctx->a.size, ctx->b.size);
		if (cost < best)
		{
			best = cost;
			*best_pa = i;
			*best_tb = tb;
		}
		i++;
	}
}
