/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:21:22 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 00:01:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	if (str && *str)
		return (1 + ft_strlen(str + 1));
	return (0);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*dst;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (n < len)
		len = n;
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	dst_len;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (strdup(""));
	dst_len = ft_strlen(s + start);
	if (len < dst_len)
		dst_len = len;
	dst = malloc((dst_len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < dst_len)
	{
		dst[i] = s[start + i];
		i++; 
	}
	dst[i] = '\0';
	return (dst);
}