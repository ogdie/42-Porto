/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:37:05 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:38:16 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew(malloc(1));
	lst->next = ft_lstnew(malloc(1));

	ft_lstclear(&lst, free);

	printf("list cleared\n");

	return (0);
}*/
