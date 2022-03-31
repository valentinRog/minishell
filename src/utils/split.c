/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:42:16 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/31 10:10:36 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s, char c)
{
	int	wc;

	wc = 0;
	if (*s && *s != c)
		wc++;
	if (*s)
		s++;
	while (*s)
	{
		if (*(s - 1) == c && *s != c)
			wc++;
		s++;
	}
	return (wc);
}

static char	const	*get_word_ptr(char const *s, char c, int n)
{
	int	wc;

	wc = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (wc == n)
			return (s);
		while (*s != c)
			s++;
		wc++;
	}
	return (NULL);
}

static char	*get_word(char const *s, char c, int n)
{
	int			len;
	const char	*ptr;
	char		*dst;
	int			i;

	len = 0;
	ptr = get_word_ptr(s, c, n);
	while (ptr[len] && ptr[len] != c)
		len++;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (+i < len)
		dst[i] = ptr[i++];
	dst[i] = '\0';
	return (dst);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

char	**split(char const *s, char c)
{
	char	**dst;
	int		wc;
	int		i;

	if (!s)
		return (NULL);
	wc = count_words(s, c) + 1;
	dst = malloc(wc * sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < wc - 1)
	{
		dst[i] = get_word(s, c, i);
		if (!dst[i])
		{
			free_split(dst);
			return (NULL);
		}
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
