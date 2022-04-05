/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:47:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 17:54:23 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*dst;
	size_t	len;
	size_t	i;

	len = str_len(str);
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
	if (str_len(s) < start)
		return (strdup(""));
	dst_len = str_len(s + start);
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

char	*str_dup1(void)
{
	char	*dst;

	dst = malloc(sizeof(char));
	if (dst)
		*dst = '\0';
	return (dst);
}

void	str_n_insert(char **astr, char *str, size_t i, size_t n)
{
	char	*dst;

	if (!astr || !*astr || !str)
		return ;
	dst = malloc((str_len(*astr) + str_len(str) + 1) * sizeof(char));
	if (dst)
	{
		str_n_cpy(dst, *astr, i);
		str_n_cpy(dst + i, str, n);
		str_n_cpy(dst + i + min(str_len(str), n), *astr + i, str_len(*astr));
	}
	free(*astr);
	*astr = dst;
}
