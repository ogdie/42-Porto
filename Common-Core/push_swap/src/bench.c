/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:14:38 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:05:39 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*strategy_name(t_strategy strategy)
{
	if (strategy == STRAT_SIMPLE)
		return ("simple");
	if (strategy == STRAT_MEDIUM)
		return ("medium");
	if (strategy == STRAT_COMPLEX)
		return ("complex");
	return ("adaptive");
}

static char	*strategy_complexity(t_strategy strategy)
{
	if (strategy == STRAT_SIMPLE)
		return ("O(n^2)");
	if (strategy == STRAT_MEDIUM)
		return ("O(n sqrt(n))");
	if (strategy == STRAT_COMPLEX)
		return ("O(n log n)");
	return ("adaptive");
}

static void	print_percent(double value)
{
	int	percent;

	percent = (int)(value * 10000.0 + 0.5);
	ft_putnbr_fd(percent / 100, 2);
	ft_putstr_fd(".", 2);
	if (percent % 100 < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(percent % 100, 2);
	ft_putstr_fd("%", 2);
}

static void	print_count(char *name, int count)
{
	ft_putstr_fd("[bench] ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_ctx *ctx)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	print_percent(ctx->disorder);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putstr_fd(strategy_name(ctx->used), 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(strategy_complexity(ctx->used), 2);
	ft_putstr_fd("\n", 2);
	print_count("total", ctx->stats.total);
	print_count("sa", ctx->stats.sa);
	print_count("sb", ctx->stats.sb);
	print_count("ss", ctx->stats.ss);
	print_count("pa", ctx->stats.pa);
	print_count("pb", ctx->stats.pb);
	print_count("ra", ctx->stats.ra);
	print_count("rb", ctx->stats.rb);
	print_count("rr", ctx->stats.rr);
	print_count("rra", ctx->stats.rra);
	print_count("rrb", ctx->stats.rrb);
	print_count("rrr", ctx->stats.rrr);
}
