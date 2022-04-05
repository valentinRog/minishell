/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:47:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 18:46:59 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_n_dup(char *str, size_t n)
{
	char	*dst;
	size_t	i;

	dst = malloc((min(str_len(str), n) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*str_n_dup1(void)
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
