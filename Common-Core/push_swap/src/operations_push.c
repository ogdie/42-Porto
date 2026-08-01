/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:59:51 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 17:12:30 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_push(t_ctx *ctx, char *op)
{
	if (!ft_strcmp(op, "pa\n"))
		ctx->stats.pa++;
	else
		ctx->stats.pb++;
	ctx->stats.total++;
	ft_putstr_fd(op, 1);
}

static int	pop_top(t_stack *stack, int *value)
{
	int	i;

	if (stack->size == 0)
		return (0);
	*value = stack->data[0];
	i = 0;
	while (i + 1 < stack->size)
	{
		stack->data[i] = stack->data[i + 1];
		i++;
	}
	stack->size--;
	return (1);
}

void	op_pa(t_ctx *ctx, int print)
{
	int	value;
	int	did;

	did = pop_top(&ctx->b, &value);
	if (did)
		push_top(&ctx->a, value);
	if (print && did)
		count_push(ctx, "pa\n");
}

void	op_pb(t_ctx *ctx, int print)
{
	int	value;
	int	did;

	did = pop_top(&ctx->a, &value);
	if (did)
		push_top(&ctx->b, value);
	if (print && did)
		count_push(ctx, "pb\n");
}
