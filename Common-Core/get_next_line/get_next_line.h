/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:30:21 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/23 16:30:24 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > 2147483647
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*stash;
	size_t	len;
	size_t	cap;
}	t_gnl;

char	*get_next_line(int fd);
int		gnl_has_newline(const char *s, size_t len);
size_t	gnl_line_len(const char *s, size_t len);
void	gnl_shift(t_gnl *gnl, size_t used);
void	gnl_clear(t_gnl *gnl);
void	*ft_malloc_zero(size_t count, size_t size);

#endif
