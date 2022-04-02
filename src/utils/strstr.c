/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:35:12 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 16:39:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (ptr[i] == needle[i] && ptr[i] && needle[i])
			i++;
		if (i == ft_strlen(needle))
			return (ptr);
		ptr++;
	}
	return (NULL);
}
