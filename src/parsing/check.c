/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:22:17 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/11 16:33:32 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_word(char **str)
{
	char	*ptr;
	size_t	len;

	ptr = (*str);
	len = 0;
	while (is_in_str(WHITESPACES, *ptr))
		ptr++;
	while (*ptr)
	{
		if(!is_in_quote(*str, QUOTES, ptr - *str) && is_in_str(WHITESPACES RESERVED, *ptr))
			break ;
		ptr++;
		len++;
	}
	while (is_in_str(WHITESPACES, *ptr))
		ptr++;
	*str = ptr;
	return (len);
}

bool	check(char *str)
{
	while (*str)
	{
		if (!str_n_cmp("<<", str, str_len("<<")))
		{
			str += 2;
			if (!skip_word(&str))
				return true;
		}
		else
			str++;	
	}
	return (false);
}