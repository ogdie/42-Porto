/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:44:04 by diemonte          #+#    #+#             */
/*   Updated: 2026/05/01 12:07:35 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdlib.h>
#include <unistd.h>

void	*to_next_char(void *content)
{
	char	*new;

	new = malloc(1);
	if (!new)
		return (NULL);
	*new = *(char *)content + 1;
	return (new);
}

int	main(void)
{
	t_list	*lst;
	t_list	*new_lst;

	lst = ft_lstnew(malloc(1));
	*(char *)lst->content = 'A';

	lst->next = ft_lstnew(malloc(1));
	*(char *)lst->next->content = 'B';

	new_lst = ft_lstmap(lst, to_next_char, free);

	// opcional: ver resultado
	while (new_lst)
	{
		write(1, new_lst->content, 1);
		new_lst = new_lst->next;
	}

	return (0);
}*/
