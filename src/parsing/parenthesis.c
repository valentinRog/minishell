/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:29:50 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/30 16:30:13 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	z_index(enum e_z z)
{
	static int	z_index;

	if (z == z_INCR)
		z_index++;
	else if (z == z_DECR)
		z_index--;
	else if (z == z_RESET)
		z_index = 0;
	return (z_index);
}

bool	parenthesis(t_cmd *cmd, char *arg, char *con)
{
	if (!str_cmp("(", con))
	{
		if (cmd->args || cmd->heredoc || cmd->outfiles || cmd->infile)
			return (true);
		z_index(z_INCR);
	}
	if (!str_cmp(")", con))
	{
		z_index(z_DECR);
		if (arg && *arg)
			return (true);
	}
	else
		cmd->z_index = z_index(z_NONE);
	return (false);
}
