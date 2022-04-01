/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:40:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 00:07:34 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	word_len(const char *str, char *charset, char *quotes)
{
	size_t	len;
	char	*start;
	char	quote;
	size_t	i;

	start = (char *)str;
	while (is_in_str(*start, charset))
		start++;
	len = 0;
	quote = '\0';
	i = 0;
	while (start[i])
	{
		if (start[i] == quote)
			quote = '\0';
		else if (!quote && is_in_str(start[i], quotes))
				quote = start[i];
		else if (!quote && is_in_str(start[i], charset))
			break ;
		else
			len++;
		i++;
	}
	return (len);
}

static void	cpy_word(char *dst, const char *str, char *charset, char *quotes)
{
	char	*start;
	char	quote;
	size_t	i;

	start = (char *)str;
	while (is_in_str(*start, charset))
		start++;
	i = 0;
	while (*start)
	{
		if (*start == quote)
			quote = '\0';
		else if (!quote && is_in_str(*start, quotes))
				quote = *start;
		else if (!quote && is_in_str(*start, charset))
			break ;
		else
		{
			dst[i] = *start;
			i++;
		}
		start++;
	}
	dst[i] = 0;
}

char	*get_next_word(const char *str, char *charset, char *quotes)
{
	size_t	len;
	char	*word;

	len = word_len(str, charset, quotes);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	cpy_word(word, str, charset, quotes);
	if (!*word)
	{
		free(word);
		return (NULL);
	}
	return (word);
}

void	skip_next_word(char **ptr, char *charset, char *quotes)
{
	char	quote;

	while (is_in_str(**ptr, charset))
		(*ptr)++;
	quote = '\0';
	while (**ptr)
	{
		if (**ptr == quote)
			quote = '\0';
		else if (!quote && is_in_str(**ptr, quotes))
				quote = **ptr;
		else if (!quote && is_in_str(**ptr, charset))
			break ;
		(*ptr)++;
	}
}
