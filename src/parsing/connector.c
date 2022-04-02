/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:11:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 14:14:34 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_connector_and(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "&&");
	if (ptr)
	{
		*ptr = ' ';
		*(ptr + 1) = ' ';
		cmd->connector = AND;
		delete_next_word(ptr, WHITESPACES, QUOTES);
		if (*(ptr + 2))
			return (true);
	}
	return (false);
}

bool	get_connector(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "|");
	if (ptr)
	{
		*ptr = ' ';
		if (*(ptr + 1) == '|')
		{
			*(ptr + 1) = ' ';
			cmd->connector = OR;
			if (*(ptr + 2))
				return (true);
		}
		else
		{
			cmd->connector = PIPE;
			if (*(ptr +1))
				return (true);
		}
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (get_connector_and(cmd, str));
}
