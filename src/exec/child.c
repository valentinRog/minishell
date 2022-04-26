/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:43:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 16:10:41 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_stdin(t_cmd *cmd, int i_pipe[2])
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i_pipe)
		dup2(i_pipe[PIPE_READ], STDIN_FILENO);
	close_pipe(i_pipe);
}

static void	dup_stdout(t_cmd *cmd, int o_pipe[2])
{
	if (cmd->con == con_PIPE)
	{
		dup2(o_pipe[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(o_pipe);
	}
}

void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2], t_list **alst)
{
	char	**cmds;

	dup_stdin(cmd, i_pipe);
	dup_stdout(cmd, o_pipe);
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		exec_builtin(cmd);
		exit(EXIT_SUCCESS);
	}
	cmds = lst_to_str_arr(cmd->args);
	exec(cmds);
}
