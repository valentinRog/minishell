/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:57:45 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/08 19:29:08 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		cmd->exec_args = NULL;
		cmd->infile = NULL;
		cmd->outfiles = NULL;
		cmd->append = false;
		cmd->limiters = NULL;
		cmd->connector = NULL;
		cmd->z_index = 0;
	}
}

void	del_cmd(void *args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) args;
	if (cmd)
	{
		str_arr_free(cmd->exec_args);
		if (cmd->infile)
			free(cmd->infile);
		str_arr_free(cmd->outfiles);
		str_arr_free(cmd->limiters);
		if (cmd->connector)
			free(cmd->connector);
		free(cmd);
	}
}
