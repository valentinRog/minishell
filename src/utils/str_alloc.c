/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:41:37 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/20 15:41:50 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_n_dup(char *src, size_t n)
{
	char	*dst;

	dst = malloc((min(str_len(src), n) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	str_n_cpy(dst, src, n);
	return (dst);
}

char	*str_dup(char *src)
{
	return (str_n_dup(src, strlen(src)));
}

char	*str_dup1(void)
{
	return (str_dup(""));
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

void	str_n_remove(char **astr, size_t i, size_t n)
{
	char	*dst;
	size_t	shift;

	shift = min(str_len((*astr) + i), n);
	dst = malloc(((str_len(*astr) - shift) + 1) * sizeof(char));
	if (dst)
	{
		str_n_cpy(dst, *astr, i);
		str_n_cpy(dst + i, (*astr) + i + shift, str_len(*astr));
	}
	free(*astr);
	*astr = dst;
}