/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:22:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/12 09:13:00 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	con_len(char *str, size_t i, char **cons, char *quotes)
{
	while (*cons)
	{
		if (!is_in_quote(str, quotes, i))
		{
			if (!str_n_cmp(str + i, *cons, str_len(*cons)))
				return (str_len(*cons));
		}
		cons++;
	}
	return (0);
}

char	*str_tok(char **astr, char *str, char **cons, char *quotes)
{
	static char	*ptr;
	char		*start;
	size_t		len;

	if (!str || !ptr)
		ptr = str;
	if (!astr || !str || !cons)
		return (NULL);
	start = ptr;
	while (*ptr)
	{
		len = con_len(str, ptr - str, cons, quotes);
		if (len)
		{
			*astr = str_n_dup(start, ptr - start);
			ptr += len;
			if (!*astr)
				return (NULL);
			return (str_n_dup(ptr - len, len));
		}
		ptr++;
	}
	*astr = str_n_dup(start, ptr - start);
	return (NULL);
}

char	*str_tok_simple(char *str, char sep, char *quotes)
{
	static char	*ptr;
	char		*start;
	char		*dst;

	if (!str || !ptr)
		ptr = str;
	if (!str)
		return (NULL);
	start = ptr;
	while (*ptr)
	{
		if (!is_in_quote(str, quotes, ptr - str) && *ptr == sep)
		{
			ptr++;
			return (str_n_dup(start, ptr - start - 1));
		}
		ptr++;
	}
	if (ptr - start)
		return (str_n_dup(start, ptr - start));
	return (NULL);
}
