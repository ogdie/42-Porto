/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 19:11:22 by diemonte          #+#    #+#             */
/*   Updated: 2026/06/14 01:20:54 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_strategy
{
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
	STRAT_ADAPTIVE
}	t_strategy;
typedef struct s_stack
{
	int	*data;
	int	size;
	int	capacity;
}	t_stack;
typedef struct s_stats
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
	int	total;
}	t_stats;
typedef struct s_ctx
{
	t_stack		a;
	t_stack		b;
	t_stats		stats;
	t_strategy	requested;
	t_strategy	used;
	int			bench;
	double		disorder;
}	t_ctx;
int			parse_args(int argc, char **argv, t_ctx *ctx);
int			is_flag(char *arg);
int			parse_flag(char *arg, t_ctx *ctx);
int			parse_sign(char *str, int *i);
int			int_overflow(long nb, int sign);
int			init_stack(t_stack *stack, int capacity);
void		free_ctx(t_ctx *ctx);
int			push_top(t_stack *stack, int value);
int			is_sorted(t_stack *stack);
int			has_duplicate(t_stack *stack);
int			normalize_stack(t_stack *stack);
double		compute_disorder(t_stack *stack);
void		op_sa(t_ctx *ctx, int print);
void		op_sb(t_ctx *ctx, int print);
void		op_ss(t_ctx *ctx, int print);
void		op_pa(t_ctx *ctx, int print);
void		op_pb(t_ctx *ctx, int print);
void		op_ra(t_ctx *ctx, int print);
void		op_rb(t_ctx *ctx, int print);
void		op_rr(t_ctx *ctx, int print);
void		op_rra(t_ctx *ctx, int print);
void		op_rrb(t_ctx *ctx, int print);
void		op_rrr(t_ctx *ctx, int print);
void		sort_small(t_ctx *ctx);
void		sort_simple(t_ctx *ctx);
void		sort_medium(t_ctx *ctx);
void		sort_complex(t_ctx *ctx);
void		sort_adaptive(t_ctx *ctx);
void		run_sort(t_ctx *ctx);
int			medium_has_value_until(t_stack *stack, int max);
void		print_error(void);
void		print_bench(t_ctx *ctx);
void		ft_putstr_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_strcmp(char *a, char *b);
int			ft_isspace(char c);
int			ft_isdigit(char c);
int			ft_sqrt_ceil(int n);
int			simple_target_b(t_stack *b, int value);
int			simple_target_a(t_stack *a, int value);
int			simple_cost(int pos, int sz, int *fwd);
int			simple_combined(int pa, int tb, int sa, int sb);
void		simple_find_pb(t_ctx *ctx, int *best_pa, int *best_tb);
void		simple_find_pa(t_ctx *ctx, int *best_pb, int *best_ta);
void		simple_move_tops(t_ctx *ctx, int pos_a, int pos_b);
void		rotate_to_min(t_ctx *ctx);
void		push_chunk(t_ctx *ctx, int chunk_max, int chunk_size);
void		push_all_chunks(t_ctx *ctx, int size, int chunk_size);
void		pull_b_to_a(t_ctx *ctx);
int			find_max_pos(t_stack *s);
int			find_min_pos(t_stack *s);
int			get_max(int a, int b);

#endif
