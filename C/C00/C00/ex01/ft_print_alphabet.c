/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:54:37 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/21 12:31:01 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_alphabet(void)
{
	char	letras;

	letras = 'a';
	while (letras <= 'z')
	{
		write (1, &letras, 1);
		letras++;
	}
}
/* int	main(void)
{
	ft_print_alphabet();
	return (0);
}*/
