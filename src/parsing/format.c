/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:23:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/11 18:10:28 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_space(char **astr)
{
	char	*ptr;
	size_t	n;

	ptr = *astr;
	n = 0;
	while (*ptr)
	{
		n = 0;
		while (is_in_str(WHITESPACES, *(ptr + n)))
			n++;
		if (n > 1)
		{
			str_n_remove(astr, ptr - *astr, n - 1);
			return format_space(astr);
		}
		ptr++;
	}	
}

void	format(char **astr)
{
	format_space(astr);
	printf("%s\n", *astr);
}
