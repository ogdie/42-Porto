/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemonte <diemonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:36:58 by diemonte          #+#    #+#             */
/*   Updated: 2026/04/26 16:39:16 by diemonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*word_dup(char const *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	free_all(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

static size_t	get_next_word(char const *s, char c, size_t i, size_t *start)
{
	while (s[i] && s[i] == c)
		i++;
	*start = i;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		i = get_next_word(s, c, i, &start);
		arr[j] = word_dup(s, start, i);
		if (!arr[j])
			return (free_all(arr, j), NULL);
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	**res;
	int		i;

	res = ft_split("hello world 42", ' ');

	if (!res)
		return (0);

	i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	printf("%p\n", res[i]);
	return (0);
}*/
