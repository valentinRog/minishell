/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:42:16 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 00:01:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s, char *charset)
{
	int	wc;

	wc = 0;
	if (*s && !is_in_str(*s, charset))
		wc++;
	if (*s)
		s++;
	while (*s)
	{
		if (is_in_str(*(s - 1), charset) && !is_in_str(*s, charset))
			wc++;
		s++;
	}
	return (wc);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	skip_word(char **ptr, char *word)
{
	while (**ptr && *word && **ptr == *word)
	{
		(*ptr)++;
		word++;
	}
}

char	**ft_split(char const *s, char *charset, char *quotes)
{
	char	**dst;
	int		wc;
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	wc = count_words(s, charset) + 1;
	dst = malloc(wc * sizeof(char *));
	if (!dst)
		return (NULL);
	i = -1;
	ptr = (char *)s;
	while (++i < wc - 1)
	{
		dst[i] = get_next_word(ptr, charset, NULL);
		if (!dst[i])
		{
			free_split(dst);
			return (NULL);
		}
		skip_next_word(&ptr, charset, quotes);
	}
	dst[i] = NULL;
	return (dst);
}
