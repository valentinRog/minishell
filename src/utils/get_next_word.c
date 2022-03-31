/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:40:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 00:44:31 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_word(const char *str, char *charset)
{
	char	*ptr;
	size_t	len;
	char	*word;

	ptr = (char *)str;
	while (is_in_str(*ptr, charset))
		ptr++;
	len = 0;
	while (ptr[len] && !is_in_str(ptr[len], charset))
		len++;
	word = ft_substr(str, ptr - str, len);
	if (!word)
		return (NULL);
	if (!*word)
	{
		free(word);
		return (NULL);
	}
	return (word);
}

void	skip_next_word(char	**ptr, char *charset)
{
	if (ptr && *ptr && charset)
	{
		while (**ptr && is_in_str(**ptr, charset))
			(*ptr)++;
		while (**ptr && !is_in_str(**ptr, charset))
			(*ptr)++;
	}
}
