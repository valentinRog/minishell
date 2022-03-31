/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:57:45 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/31 10:02:46 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*content;

	content = malloc(sizeof(t_cmd));
	if (!content)
		return (NULL);
	return (content);
}

void	init_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		cmd->exec_args = NULL;
		cmd->infile = NULL;
		cmd->outfile = NULL;
		cmd->append = false;
		cmd->limiter = NULL;
		cmd->pipe = false;
	}
}
