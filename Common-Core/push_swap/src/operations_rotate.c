/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:12:45 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 17:28:08 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_rotate(t_ctx *ctx, char *op)
{
	if (!ft_strcmp(op, "ra\n"))
		ctx->stats.ra++;
	else if (!ft_strcmp(op, "rb\n"))
		ctx->stats.rb++;
	else
		ctx->stats.rr++;
	ctx->stats.total++;
	ft_putstr_fd(op, 1);
}

static void	rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack->size < 2)
		return ;
	tmp = stack->data[0];
	i = 0;
	while (i + 1 < stack->size)
	{
		stack->data[i] = stack->data[i + 1];
		i++;
	}
	stack->data[stack->size - 1] = tmp;
}

void	op_ra(t_ctx *ctx, int print)
{
	if (ctx->a.size > 1)
	{
		rotate(&ctx->a);
		if (print)
			count_rotate(ctx, "ra\n");
	}
}

void	op_rb(t_ctx *ctx, int print)
{
	if (ctx->b.size > 1)
	{
		rotate(&ctx->b);
		if (print)
			count_rotate(ctx, "rb\n");
	}
}

void	op_rr(t_ctx *ctx, int print)
{
	int	did_a;
	int	did_b;

	did_a = ctx->a.size > 1;
	did_b = ctx->b.size > 1;
	if (did_a)
		rotate(&ctx->a);
	if (did_b)
		rotate(&ctx->b);
	if (print && (did_a || did_b))
		count_rotate(ctx, "rr\n");
}
