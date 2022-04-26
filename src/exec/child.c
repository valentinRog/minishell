/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:43:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 14:52:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2], t_list **alst)
{
	char	**cmds;

	cmds = lst_to_str_arr(cmd->args);
	if (i_pipe)
	{
		dup2(i_pipe[PIPE_READ], STDIN_FILENO);
		close_pipe(i_pipe);
	}
	else if (cmd->con == con_PIPE)
	{
		dup2(o_pipe[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(o_pipe);
	}
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		exec_builtin(cmd);
		exit(EXIT_SUCCESS);
	}
	exec(cmds);
}
