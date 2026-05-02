/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:34:36 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:36:26 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*node;

	node = ft_lstnew(malloc(1));
	if (!node)
		return (1);

	ft_lstdelone(node, free);

	printf("node deleted\n");

	return (0);
}*/
