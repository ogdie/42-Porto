/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reverse_alphabet.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmenezes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:29:57 by dmenezes          #+#    #+#             */
/*   Updated: 2025/02/21 13:33:34 by dmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_reverse_alphabet(void)
{
	char	letras;

	letras = 'z';
	while (letras >= 'a')
	{
		write(1, &letras, 1);
		letras--;
	}
}
/*int	main(void)
{
	ft_print_reverse_alphabet();
	return (0);
}*/
