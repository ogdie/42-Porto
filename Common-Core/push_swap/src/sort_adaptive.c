/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:13:17 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/30 19:14:21 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_ctx *ctx)
{
	if (ctx->a.size <= 5)
	{
		ctx->used = STRAT_SIMPLE;
		sort_small(ctx);
	}
	else if (ctx->disorder < 0.2)
	{
		ctx->used = STRAT_SIMPLE;
		sort_simple(ctx);
	}
	else if (ctx->disorder < 0.5)
	{
		ctx->used = STRAT_MEDIUM;
		sort_medium(ctx);
	}
	else
	{
		ctx->used = STRAT_COMPLEX;
		sort_complex(ctx);
	}
}

void	run_sort(t_ctx *ctx)
{
	if (is_sorted(&ctx->a))
		return ;
	if (ctx->requested == STRAT_SIMPLE)
	{
		ctx->used = STRAT_SIMPLE;
		sort_simple(ctx);
	}
	else if (ctx->requested == STRAT_MEDIUM)
	{
		ctx->used = STRAT_MEDIUM;
		sort_medium(ctx);
	}
	else if (ctx->requested == STRAT_COMPLEX)
	{
		ctx->used = STRAT_COMPLEX;
		sort_complex(ctx);
	}
	else
		sort_adaptive(ctx);
}
