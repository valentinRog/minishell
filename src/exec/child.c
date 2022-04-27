/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:43:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 18:20:54 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2], t_shell *shell)
{
	char	**cmds;

	if (dup_stdin(cmd, i_pipe, shell) || dup_stdout(cmd, o_pipe))
	{
		exec_error(NULL, shell, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		if (exec_builtin(cmd))
		{
			exec_error(cmd->args->content, shell, NULL, NULL);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	cmds = lst_to_str_arr(cmd->args);
	if (!cmds)
	{
		exec_error("lst_to_str_arr", shell, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	exec(cmds, shell);
}
