/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:07:52 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:07:56 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(char *arg)
{
	return (!ft_strcmp(arg, "--simple") || !ft_strcmp(arg, "--medium")
		|| !ft_strcmp(arg, "--complex") || !ft_strcmp(arg, "--adaptive")
		|| !ft_strcmp(arg, "--bench"));
}

int	parse_flag(char *arg, t_ctx *ctx)
{
	if (!ft_strcmp(arg, "--simple"))
		ctx->requested = STRAT_SIMPLE;
	else if (!ft_strcmp(arg, "--medium"))
		ctx->requested = STRAT_MEDIUM;
	else if (!ft_strcmp(arg, "--complex"))
		ctx->requested = STRAT_COMPLEX;
	else if (!ft_strcmp(arg, "--adaptive"))
		ctx->requested = STRAT_ADAPTIVE;
	else if (!ft_strcmp(arg, "--bench"))
		ctx->bench = 1;
	else
		return (0);
	return (1);
}

int	parse_sign(char *str, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[(*i)++] == '-')
			return (-1);
	}
	return (1);
}

int	int_overflow(long nb, int sign)
{
	return ((sign == 1 && nb > INT_MAX) || (sign == -1 && nb > -(long)INT_MIN));
}
