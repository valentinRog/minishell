/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:21:22 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 18:56:45 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	str_len(char *str)
{
	if (str && *str)
		return (1 + str_len(str + 1));
	return (0);
}

bool	is_in_str(char *str, char c)
{
	if (str && *str)
	{
		if (*str == c)
			return (true);
		return (is_in_str(str + 1, c));
	}
	return (false);
}

bool	is_in_quote(char *str, char *quotes, size_t index)
{
	char	quote;
	size_t	i;

	quote = '\0';
	i = 0;
	while (i != index)
	{
		if (!str[i])
			return (false);
		if (!quote && is_in_str(quotes, str[i]))
			quote = str[i];
		else if (quote == str[i])
			quote = '\0';
		i++;
	}
	if (quote)
		return (true);
	return (false);
}

void	str_n_cpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst && src)
	{
		while (src[i] && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}
