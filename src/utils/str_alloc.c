/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:47:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 20:50:31 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	str_append_buff(char **astr, char *buff, size_t size)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!astr || !buff || !*buff || !size)
		return ;
	if (!*astr)
		*astr = strdup("");
	dst = malloc((ft_strlen(*astr) + size + 1) * sizeof(char));
	if (dst)
		copy_buff(dst, astr, buff, size);
	free(*astr);
	*astr = dst;
}
