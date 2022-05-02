/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:19:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/29 15:35:03 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_str(char *str, char c)
{
	if (str && *str)
	{
		if (*str == c)
			return (true);
		return (in_str(str + 1, c));
	}
	return (false);
}

char	in_quote(char *str, char *quotes, size_t index)
{
	char	quote;
	size_t	i;

	quote = '\0';
	i = 0;
	while (i != index && str[i])
	{
		if (!quote && in_str(quotes, str[i]))
			quote = str[i];
		else if (quote == str[i])
			quote = '\0';
		i++;
	}
	return (quote);
}

char	*str_chr(char *str, char c)
{
	if (!str || !*str)
		return (NULL);
	if (*str == c)
		return (str);
	return (str_chr(str + 1, c));
}

bool	is_tok(char *str, char *tokens, char sep)
{
	char	*ptr;

	if (!tokens || !str)
		return (false);
	ptr = tokens;
	while (*ptr && *ptr != sep)
		ptr++;
	if
		(
		!str_n_cmp(str, tokens, str_len(str))
		&& (int64_t)str_len(str) == ptr - tokens
		)
		return (true);
	if (*ptr)
		return (is_tok(str, ptr + 1, sep));
	return (false);
}
