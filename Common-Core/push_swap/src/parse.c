/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfaria-c <jfaria-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 19:15:59 by jfaria-c          #+#    #+#             */
/*   Updated: 2026/06/16 16:07:32 by jfaria-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_numbers_in_arg(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static int	total_numbers(int argc, char **argv)
{
	int	i;
	int	total;

	i = 1;
	total = 0;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			i++;
		else
			total += count_numbers_in_arg(argv[i++]);
	}
	return (total);
}

static int	parse_number(char *str, int *i, int *out)
{
	long	nb;
	int		sign;
	int		digits;

	while (ft_isspace(str[*i]))
		(*i)++;
	sign = parse_sign(str, i);
	nb = 0;
	digits = 0;
	while (ft_isdigit(str[*i]))
	{
		nb = nb * 10 + (str[(*i)++] - '0');
		if (int_overflow(nb, sign))
			return (0);
		digits++;
	}
	if (!digits || (str[*i] && !ft_isspace(str[*i])))
		return (0);
	*out = (int)(nb * sign);
	return (1);
}

static int	parse_values_from_arg(char *arg, t_stack *a)
{
	int	i;
	int	value;
	int	found;

	i = 0;
	found = 0;
	while (arg[i])
	{
		while (ft_isspace(arg[i]))
			i++;
		if (!arg[i])
			break ;
		if (!parse_number(arg, &i, &value))
			return (0);
		a->data[a->size++] = value;
		found = 1;
	}
	return (found);
}

int	parse_args(int argc, char **argv, t_ctx *ctx)
{
	int	i;
	int	count;

	ctx->requested = STRAT_ADAPTIVE;
	ctx->used = STRAT_ADAPTIVE;
	count = total_numbers(argc, argv);
	if (!init_stack(&ctx->a, count) || !init_stack(&ctx->b, count))
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			if (!parse_flag(argv[i], ctx))
				return (0);
		}
		else if (argv[i][0] == '\0' || !parse_values_from_arg(argv[i], &ctx->a))
			return (0);
	}
	return (!has_duplicate(&ctx->a));
}
