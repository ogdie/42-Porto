/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:27:04 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 17:27:54 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_op(t_ctx *ctx, char *op)
{
	if (!ft_strcmp(op, "sa\n"))
		ctx->stats.sa++;
	else if (!ft_strcmp(op, "sb\n"))
		ctx->stats.sb++;
	else
		ctx->stats.ss++;
	ctx->stats.total++;
	ft_putstr_fd(op, 1);
}

void	op_sa(t_ctx *ctx, int print)
{
	int	tmp;
	int	did;

	did = 0;
	if (ctx->a.size > 1)
	{
		tmp = ctx->a.data[0];
		ctx->a.data[0] = ctx->a.data[1];
		ctx->a.data[1] = tmp;
		did = 1;
	}
	if (print && did)
		count_op(ctx, "sa\n");
}

void	op_sb(t_ctx *ctx, int print)
{
	int	tmp;
	int	did;

	did = 0;
	if (ctx->b.size > 1)
	{
		tmp = ctx->b.data[0];
		ctx->b.data[0] = ctx->b.data[1];
		ctx->b.data[1] = tmp;
		did = 1;
	}
	if (print && did)
		count_op(ctx, "sb\n");
}

void	op_ss(t_ctx *ctx, int print)
{
	int	did_a;
	int	did_b;

	did_a = ctx->a.size > 1;
	did_b = ctx->b.size > 1;
	if (did_a)
		op_sa(ctx, 0);
	if (did_b)
		op_sb(ctx, 0);
	if (print && (did_a || did_b))
		count_op(ctx, "ss\n");
}
