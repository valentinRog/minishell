/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:42:16 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 20:09:25 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char const *s, char *charset, char *quotes)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	skip_white_space(&ptr, charset, quotes);
	while (*ptr)
	{
		skip_next_word(&ptr, charset, quotes);
		skip_white_space(&ptr, charset, quotes);
		i++;
	}
	return (i);
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

char	**ft_split(char const *s, char *charset, char *quotes)
{
	char	**dst;
	size_t	wc;
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	wc = count_words(s, charset, quotes);
	dst = malloc((wc + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	i = -1;
	ptr = (char *)s;
	while (++i < wc)
	{
		dst[i] = get_next_word(ptr, charset, quotes);
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
