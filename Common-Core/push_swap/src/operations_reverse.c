/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 17:28:22 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 17:36:44 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_reverse(t_ctx *ctx, char *op)
{
	if (!ft_strcmp(op, "rra\n"))
		ctx->stats.rra++;
	else if (!ft_strcmp(op, "rrb\n"))
		ctx->stats.rrb++;
	else
		ctx->stats.rrr++;
	ctx->stats.total++;
	ft_putstr_fd(op, 1);
}

static void	reverse_rotate(t_stack *stack)
{
	int	tmp;
	int	i;

	if (stack->size < 2)
		return ;
	tmp = stack->data[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->data[i] = stack->data[i - 1];
		i--;
	}
	stack->data[0] = tmp;
}

void	op_rra(t_ctx *ctx, int print)
{
	if (ctx->a.size > 1)
	{
		reverse_rotate(&ctx->a);
		if (print)
			count_reverse(ctx, "rra\n");
	}
}

void	op_rrb(t_ctx *ctx, int print)
{
	if (ctx->b.size > 1)
	{
		reverse_rotate(&ctx->b);
		if (print)
			count_reverse(ctx, "rrb\n");
	}
}

void	op_rrr(t_ctx *ctx, int print)
{
	int	did_a;
	int	did_b;

	did_a = ctx->a.size > 1;
	did_b = ctx->b.size > 1;
	if (did_a)
		reverse_rotate(&ctx->a);
	if (did_b)
		reverse_rotate(&ctx->b);
	if (print && (did_a || did_b))
		count_reverse(ctx, "rrr\n");
}
