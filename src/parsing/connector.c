/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:11:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 20:06:50 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_connector_and(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = ft_strstr(str, "&&", QUOTES);
	if (ptr)
	{
		*ptr = ' ';
		*(ptr + 1) = ' ';
		cmd->connector = AND;
		delete_next_word(ptr, WHITESPACES, QUOTES);
		if (is_in_str(ptr[2], CONNECTORS))
			return (true);
	}
	return (false);
}

bool	get_connector(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = ft_strstr(str, "|", QUOTES);
	if (ptr)
	{
		*ptr = ' ';
		if (*(ptr + 1) == '|')
		{
			*(ptr + 1) = ' ';
			cmd->connector = OR;
			if (is_in_str(ptr[1], CONNECTORS))
				return (true);
		}
		else
		{
			cmd->connector = PIPE;
			if (is_in_str(ptr[2], CONNECTORS))
				return (true);
		}
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (get_connector_and(cmd, str));
}
