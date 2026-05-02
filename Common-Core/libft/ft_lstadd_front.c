/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:18:45 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:23:56 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	ft_lstadd_front(&lst, ft_lstnew("World"));
	ft_lstadd_front(&lst, ft_lstnew("Hello"));

	printf("%s\n", (char *)lst->content);
	printf("%s\n", (char *)lst->next->content);
	return (0);
}*/
