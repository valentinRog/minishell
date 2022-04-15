/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paranthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:32:09 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/15 14:47:16 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	z_index(int op)
{
	static int	z_index;

	if (op == INCR)
		z_index++;
	else if (op == DECR)
		z_index--;
	else if (op == RESET)
		z_index = 0;
	return (z_index);
}

bool	parenthesis(t_cmd *cmd, char *arg, char *con)
{
	if (!str_cmp("(", con))
	{
		if (cmd->args || cmd->limiters || cmd->outfiles || cmd->infile)
			return (true);
		z_index(INCR);
		cmd->z_index = z_index(NONE);
		if (*arg)
			lst_add_back(&cmd->args, lst_new(str_n_dup(arg, str_len(arg))));
	}
	else if (!str_cmp(")", con))
	{
		z_index(DECR);
		if (arg && *arg)
			return (true);
	}
	return (false);
}
