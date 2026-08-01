/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 18:12:10 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 18:29:47 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_ctx(t_ctx *ctx)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)ctx;
	i = 0;
	while (i < sizeof(t_ctx))
		ptr[i++] = 0;
}

static int	is_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	setup_ctx(int argc, char **argv, t_ctx *ctx)
{
	init_ctx(ctx);
	if (!parse_args(argc, argv, ctx))
		return (-1);
	if (!ctx->bench && is_sorted(&ctx->a))
		return (0);
	ctx->disorder = compute_disorder(&ctx->a);
	if (!normalize_stack(&ctx->a))
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	int		ret;

	if (argc == 1 || (argc == 2 && argv[1][0] != '\0' && is_blank(argv[1])))
		return (0);
	ret = setup_ctx(argc, argv, &ctx);
	if (ret < 0)
	{
		print_error();
		free_ctx(&ctx);
		return (1);
	}
	if (ret == 0)
	{
		free_ctx(&ctx);
		return (0);
	}
	run_sort(&ctx);
	if (ctx.bench)
		print_bench(&ctx);
	free_ctx(&ctx);
	return (0);
}
