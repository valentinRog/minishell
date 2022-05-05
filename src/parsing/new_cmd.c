/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:15:02 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 18:04:57 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		cmd->args = NULL;
		cmd->infile = NULL;
		cmd->outfiles = NULL;
		cmd->append = false;
		cmd->heredoc = NULL;
		cmd->con = con_NONE;
		cmd->z_index = 0;
	}
}

t_cmd	*new_cmd(t_cmd **dst)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	if (dst)
		*dst = cmd;
	return (cmd);
}

void	del_cmd(void *args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) args;
	if (cmd)
	{
		lst_clear(&cmd->args, free);
		free(cmd->infile);
		lst_clear(&cmd->outfiles, free);
		free(cmd->heredoc);
		free(cmd);
	}
}
