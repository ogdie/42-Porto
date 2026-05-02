/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:24:27 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 17:26:14 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	ft_lstadd_front(&lst, ft_lstnew("World"));
	ft_lstadd_front(&lst, ft_lstnew("Hello"));

	printf("Size: %d\n", ft_lstsize(lst));
	return (0);
}*/
