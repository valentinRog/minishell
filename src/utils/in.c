/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:19:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 15:21:29 by vrogiste         ###   ########.fr       */
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
