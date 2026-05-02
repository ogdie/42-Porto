/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:28:01 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:29:31 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list *a;
	t_list *b;
	t_list *c;
	t_list *last;

	a = ft_lstnew("Primeiro");
	b = ft_lstnew("Segundo");
	c = ft_lstnew("Terceiro");

	a->next = b;
	b->next = c;
	c->next = NULL;

	last = ft_lstlast(a);

	printf("Ultimo elemento: %s\n", (char *)last->content);

	return (0);
}*/
