/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 07:04:28 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/04 07:24:16 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_arg(char **dst, char *identifier, char *str)
{
	char	*ptr;
	size_t	i;

	ptr = ft_strstr(str, identifier, QUOTES);
	if (ptr)
	{
		*dst = get_next_word(ptr, WHITESPACES RESERVED, QUOTES);
		if (!*dst)
			return (true);
		i = 0;
		while (ptr[i] == identifier[i] && identifier[i])
		{
			ptr[i] = ' ';
			i++;
		}
		delete_next_word(ptr, WHITESPACES RESERVED, QUOTES);
	}
	ptr = ft_strstr(str, identifier, QUOTES);
	if (ptr)
		return (true);
	return (false);
}
