/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:13:49 by diemonte          #+#    #+#             */
/*   Updated: 2026/02/16 20:52:28 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//#include <stdio.h>

int	is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_separator(str[i], charset))
		{
			i++;
		}
		if (str[i])
		{
			count++;
		}
		while (str[i] && !is_separator(str[i], charset))
		{
			i++;
		}
	}
	return (count);
}

char	*get_word(char *str, char *charset)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (str[len] && !is_separator(str[len], charset))
	{
		len++;
	}
	word = malloc(len + 1);
	if (!word)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	int		words;
	char	**array;

	i = 0;
	j = 0;
	words = count_words(str, charset);
	array = malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] && is_separator(str[i], charset))
			i++;
		if (str[i])
		{
			array[j++] = get_word(str + i, charset);
			while (str[i] && !is_separator(str[i], charset))
				i++;
		}
	}
	array[j] = NULL;
	return (array);
}
/*
int	main(void)
{
	char	*str = "A#cadeia@que#será+transmitida#não+será@editável";
	char	*sep = "#@+";
	char	**words;
	int	i = 0;

	words = ft_split(str, sep);

	while (words[i])
	{
        	printf("%s\n", words[i]);
        	free(words[i]); // libera cada palavra
        	i++;
	}
	free(words); // libera o array de ponteiros

	return 0;
}*/
