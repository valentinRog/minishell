/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:15:03 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 20:23:57 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char *c1, char *c2)
{
	char	c_temp;

	c_temp = *c1;
	*c1 = *c2;
	*c2 = c_temp;
}

void	str_reverse(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = str_len(str);
	while (i < j && j > 0)
	{
		swap(str + i, str + j - 1);
		i++;
		j--;
	}
}
