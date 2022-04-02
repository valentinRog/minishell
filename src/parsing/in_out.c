/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:16:16 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 14:21:08 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_limiter(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "<<");
	if (ptr)
	{
		*ptr = ' ';
		*(ptr + 1) = ' ';
		cmd->limiter = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->limiter)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (false);
}

static bool	get_in(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "<");
	if (ptr)
	{
		*ptr = ' ';
		cmd->infile = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->infile)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (false);
}

bool	get_in_out(t_cmd *cmd, char *str)
{
	char	*ptr;

	if (get_in(cmd, str))
		return (true);
	ptr = strstr(str, ">");
	if (ptr)
	{
		*ptr = ' ';
		if (*(ptr + 1) == '>')
		{
			*(ptr + 1) = ' ';
			cmd->append = true;
		}
		cmd->outfile = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->outfile)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (false);
}
