/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:40:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 00:17:41 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_word(const char *str)
{
	char	*ptr;
	size_t	len;
	char	*word;

	ptr = (char *)str;
	while (*ptr == ' ')
		ptr++;
	len = 0;
	while (ptr[len] && ptr[len] != ' ')
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

void	skip_next_word(char	**ptr)
{
	if (ptr && *ptr)
	{
		while (**ptr == ' ')
			(*ptr)++;
		while (**ptr && **ptr != ' ')
			(*ptr)++;
	}
}
