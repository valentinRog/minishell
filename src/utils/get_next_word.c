/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:40:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 19:47:39 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_white_space(char **ptr, char *charset, char *quotes)
{
	char	*str;

	str = *ptr;
	while (is_in_str(*str, charset))
		str++;
	*ptr = str;
}

void	skip_next_word(char **ptr, char *charset, char *quotes)
{
	char	*str;
	char	quote;

	skip_white_space(ptr, charset, quotes);
	str = *ptr;
	quote = '\0';
	while (*str)
	{
		if (!quote && is_in_str(*str, quotes))
			quote = *str;
		else if (*str == quote)
			quote = '\0';
		else if (!quote && is_in_str(*str, charset))
			break ;
		str++;
	}
	skip_white_space(ptr, charset, quotes);
	*ptr = str;
}

void	delete_next_word(const char *str, char *charset, char *quotes)
{
	char	*ptr;
	char	quote;

	ptr = (char *)str;
	skip_white_space(&ptr, charset, quotes);
	quote = '\0';
	while (*ptr)
	{
		if (!quote && is_in_str(*ptr, quotes))
			quote = *ptr;
		else if (*ptr == quote)
			quote = '\0';
		else if (!quote && is_in_str(*ptr, charset))
			break ;
		*ptr = ' ';
		ptr++;
	}
}

char	*get_next_word(const char *str, char *charset, char *quotes)
{
	char	*word;
	char	*ptr;
	char	quote;

	word = NULL;
	ptr = (char *)str;
	skip_white_space(&ptr, charset, quotes);
	quote = '\0';
	if (!*ptr)
		return (NULL);
	word = strdup("");
	while (*ptr)
	{
		if (!quote && is_in_str(*ptr, quotes))
			quote = *ptr;
		else if (*ptr == quote)
			quote = '\0';
		else if (!quote && is_in_str(*ptr, charset))
			break ;
		else
			str_append_buff(&word, ptr, 1);
		ptr++;
	}
	return (word);
}
