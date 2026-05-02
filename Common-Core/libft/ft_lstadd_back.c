/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:31:26 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:32:46 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*lst;

	lst = NULL;

	ft_lstadd_back(&lst, ft_lstnew("A"));
	ft_lstadd_back(&lst, ft_lstnew("B"));
	ft_lstadd_back(&lst, ft_lstnew("C"));

	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");

	return (0);
}*/
