/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:47:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 21:20:26 by vrogiste         ###   ########.fr       */
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

static void	copy_buff(char *dst, char **astr, char *buff, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*astr)[i])
	{
		dst[i] = (*astr)[i];
		i++;
	}
	j = 0;
	while (j < size)
	{
		dst[i + j] = buff[j];
		j++;
	}
	dst[i + j] = '\0';
}

bool	str_append_buff(char **astr, char *buff, size_t size)
{
	char	*dst;
	size_t	i;
	size_t	j;
	bool	error;

	error = false;
	if (!astr || !buff || !size)
		return (true);
	if (!*astr)
		*astr = strdup("");
	dst = malloc((ft_strlen(*astr) + size + 1) * sizeof(char));
	if (dst)
		copy_buff(dst, astr, buff, size);
	else
		error = true;
	free(*astr);
	*astr = dst;
	return (error);
}
