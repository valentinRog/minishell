/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:47:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 14:37:33 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (dst);
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

void	str_insert(char **astr, char *str, size_t index)
{
	char	*dst;
	size_t	i;
	size_t	j;

	dst = malloc((ft_strlen(*astr) + ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	while (i < index)
	{
		dst[i] = (*astr)[i];
		i++;
	}
	j = 0;
	while (str[j])
	{
		dst[i + j] = str[j];
		j++;
	}
	while ((*astr)[i])
	{
		dst[i + j] = (*astr)[i];
		i++;
	}
	dst[i + j] = '\0';
	free(*astr);
	*astr = dst;
}