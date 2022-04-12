/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:23:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/12 18:41:58 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_redirection(char **astr)
{
	char	*ptr;
	size_t	len;
	char	**seps;

	seps = split("<<:>>:>:<", ':');
	ptr = (*astr);
	while (*ptr)
	{
		len = con_len(*astr, ptr - *astr, seps, QUOTES);
		if (len)
		{
			if (ptr > *astr && !is_in_str(WHITESPACES, *(ptr - 1)))
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
	str_arr_free(seps);
}

void	format_space(char **astr)
{
	char	*ptr;
	size_t	n;

	ptr = *astr;
	while (*ptr)
	{
		n = 0;
		while (is_in_str(WHITESPACES, ptr[n])
			&& !is_in_quote(*astr, QUOTES, ptr - *astr))
			n++;
		if (n > 1)
		{
			str_n_remove(astr, ptr - *astr, n - 1);
			return (format_space(astr));
		}
		ptr++;
	}
}

void	format_parenthesis(char **astr)
{
	char	*ptr;

	if (is_in_str(WHITESPACES, **astr))
		str_n_remove(astr, 0, 1);
}

void	format(char **astr)
{
	format_space(astr);
	format_redirection(astr);
	if (errno == ENOMEM)
	{
		free(*astr);
		*astr = NULL;
	}
	printf("%s\n", *astr);
}
