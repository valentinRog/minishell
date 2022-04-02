/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:11:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 20:22:40 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_connector_and(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = ft_strstr(str, "&&", QUOTES);
	if (ptr)
	{
		ptr[0] = ' ';
		ptr[1] = ' ';
		cmd->connector = AND;
	}
	if (ft_strstr(str, "&", QUOTES))
		return (true);
	return (false);
}

bool	get_connector(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = ft_strstr(str, "|", QUOTES);
	if (ptr)
	{
		ptr[0] = ' ';
		if (ptr[1] == '|')
		{
			ptr[1] = ' ';
			cmd->connector = OR;
		}
		else
			cmd->connector = PIPE;
	}
	if (ft_strstr(str, "|", QUOTES))
		return (true);
	return (get_connector_and(cmd, str));
}
