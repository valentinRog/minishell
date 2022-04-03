/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:40:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/03 20:52:08 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_charset(char **ptr, char *charset)
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

	skip_charset(ptr, charset);
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
	*ptr = str;
	skip_charset(ptr, charset);
}

void	delete_next_word(const char *str, char *charset, char *quotes)
{
	char	*ptr;
	char	quote;

	ptr = (char *)str;
	skip_charset(&ptr, charset);
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

bool	get_next_word(char **dst, const char *str, char *charset, char *quotes)
{
	char	*ptr;
	char	quote;
	char	*word;

	ptr = (char *)str;
	skip_charset(&ptr, charset);
	quote = '\0';
	word = NULL;
	while (*ptr)
	{
		if (!quote && is_in_str(*ptr, quotes))
			quote = *ptr;
		else if (*ptr == quote)
		{
			if (str_append_buff(&word, "", 1))
				return (true);
			quote = '\0';
		}
		else if (!quote && is_in_str(*ptr, charset))
			break ;
		else
			if (str_append_buff(&word, ptr, 1))
				return (true);
		ptr++;
	}
	*dst = word;
	return (false);
}
