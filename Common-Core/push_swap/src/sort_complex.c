/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:29:18 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/13 21:45:09 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	log2_floor(int n)
{
	int	bits;

	bits = 0;
	while (n > 1)
	{
		n >>= 1;
		bits++;
	}
	return (bits);
}

static int	complex_chunk_size(int n)
{
	int	log_n;
	int	chunk;

	log_n = log2_floor(n);
	chunk = 2 * log_n * log_n;
	if (chunk < 2)
		chunk = 2;
	return (chunk);
}

void	sort_complex(t_ctx *ctx)
{
	int	size;

	if (ctx->a.size <= 5)
	{
		sort_small(ctx);
		return ;
	}
	size = ctx->a.size;
	push_all_chunks(ctx, size, complex_chunk_size(size));
	pull_b_to_a(ctx);
	rotate_to_min(ctx);
}
