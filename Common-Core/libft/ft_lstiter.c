/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:38:58 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:41:54 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include <stdlib.h>
void	add_one(void *content)
{
	*(char *)content += 1;
}

int	main(void)
{
	t_list	*lst;

	lst = ft_lstnew(malloc(1));
	*(char *)lst->content = 'A';

	ft_lstiter(lst, add_one);

	printf("%c\n", *(char *)lst->content);

	return (0);
}*/
