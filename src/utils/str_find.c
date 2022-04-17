/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:19:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/17 18:36:19 by vrogiste         ###   ########.fr       */
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

bool	in_quote(char *str, char *quotes, size_t index)
{
	char	quote;
	size_t	i;

	quote = '\0';
	i = 0;
	while (i != index)
	{
		if (!str[i])
			return (false);
		if (!quote && in_str(quotes, str[i]))
			quote = str[i];
		else if (quote == str[i])
			quote = '\0';
		i++;
	}
	if (quote)
		return (true);
	return (false);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n)
		return (NULL);
	if (*((unsigned char *) s) == (unsigned char) c)
		return ((void *) s);
	return (ft_memchr(s + 1, c, n - 1));
}

bool	is_tok(char *str, char *tokens, char sep)
{
	char	*ptr;

	if (!tokens || !str)
		return (false);
	ptr = tokens;
	while (*ptr && *ptr != sep)
		ptr++;
	if (!str_cmp(str, tokens) && (int64_t) str_len(str) == ptr - tokens)
		return (true);
	if (*ptr)
		return (is_tok(str, ptr + 1, sep));
	return (false);
}
