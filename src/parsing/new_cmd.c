/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:57:45 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/07 21:55:36 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		cmd->exec_args = NULL;
		cmd->infiles = NULL;
		cmd->outfiles = NULL;
		cmd->append_files = NULL;
		cmd->limiter = NULL;
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
		str_arr_free(cmd->infiles);
		str_arr_free(cmd->outfiles);
		str_arr_free(cmd->append_files);
		if (cmd->limiter)
			free(cmd->limiter);
		if (cmd->connector)
			free(cmd->connector);
		free(cmd);
	}
}
