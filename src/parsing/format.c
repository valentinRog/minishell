/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:23:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/12 17:06:16 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_redirection(char **astr)
{
	char	*ptr;
	size_t	len;

	ptr = *astr;
	while (*ptr)
	{
		len = con_len(*astr, ptr - *astr, split("<<:>>:>:<", ':'), QUOTES);
		if (len)
		{
			if (ptr - 1 >= *astr && !is_in_str(WHITESPACES, *(ptr - 1)))
			{
				str_n_insert(astr, " ", (ptr) - *astr, 1);
				return (format_redirection(astr));
			}
			ptr += len;
			if (is_in_str(WHITESPACES, *ptr))
			{
				str_n_remove(astr, ptr - *astr, 1);
				return (format_redirection(astr));
			}
		}
		ptr++;
	}	
}

void	format_space(char **astr)
{
	char	*ptr;
	size_t	n;

	ptr = *astr;
	n = 0;
	while (*ptr)
	{
		n = 0;
		while (is_in_str(WHITESPACES, *(ptr + n)) && !is_in_quote(*astr, QUOTES, ptr - *astr))
			n++;
		if (ptr == *astr && *ptr == ' ')
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
	//format_redictions(astr);
	format_redirection(astr);
	printf("%s\n", *astr);
}
