/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:21:22 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/04 07:18:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	if (str && *str)
		return (1 + ft_strlen(str + 1));
	return (0);
}

bool	is_in_str(char c, const char *str)
{
	if (str && *str)
	{
		if (*str == c)
			return (true);
		return (is_in_str(c, str + 1));
	}
	return (false);
}

static void	skip_quotes(char **ptr, char *quotes)
{
	char	quote;

	if (is_in_str(**ptr, quotes))
	{
		quote = **ptr;
		(*ptr)++;
		while (**ptr)
		{
			if (**ptr == quote)
			{
				(*ptr)++;
				break ;
			}
			(*ptr)++;
		}
	}
}

char	*ft_strstr(const char *haystack, const char *needle, char *quotes)
{
	size_t	i;
	char	*ptr;

	if (!haystack || !needle || !quotes)
		return (NULL);
	ptr = (char *)haystack;
	if (*needle == '\0')
		return (ptr);
	while (*ptr)
	{
		skip_quotes(&ptr, quotes);
		i = 0;
		while (ptr[i] == needle[i] && ptr[i])
			i++;
		if (!needle[i])
			return (ptr);
		ptr++;
	}
	return (NULL);
}
