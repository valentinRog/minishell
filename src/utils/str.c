/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:21:22 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 15:52:08 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	if (str && *str)
		return (1 + ft_strlen(str + 1));
	return (0);
}

bool	is_in_str(char c, const char *str)
{
	if (str && *str)
	{
		if (*str == c)
			return (true);
		return (is_in_str(c, str + 1));
	}
	return (false);
}

