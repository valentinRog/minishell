/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:23:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/12 19:59:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	format_dst(char *str, char **adst)
{
		
}

void	format(char **astr)
{
	char	*src;
	char	*dst;

	src = *astr;
	dst = str_n_dup1();
	free(src);
	*astr = dst;
}
