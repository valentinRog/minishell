/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:43:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 18:27:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	dup_stdin(t_cmd *cmd, int i_pipe[2])
{
	int	fd;
	int	ret;

	ret = 0;
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			close_pipe(i_pipe);
			return (true);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i_pipe)
		ret = dup2(i_pipe[PIPE_READ], STDIN_FILENO);
	close_pipe(i_pipe);
	if (ret == -1)
		return (true);
	return (false);
}

static bool	dup_stdout(t_cmd *cmd, int o_pipe[2])
{
	int	fd;
	int	ret;

	if (cmd->outfiles)
	{
		fd = open((char *)cmd->outfiles->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
		{
			close_pipe(o_pipe);
			return (true);
		}
		ret = dup2(fd, STDOUT_FILENO);
		close(fd);
		if (cmd->con == con_PIPE)
			close_pipe(o_pipe);
		if (ret == -1)
			return (true);
	}
	else if (cmd->con == con_PIPE)
	{
		ret = dup2(o_pipe[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(o_pipe);
		if (ret == -1)
			return (true);
	}
	return (false);
}

void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2], t_list **alst)
{
	char	**cmds;

	if (dup_stdin(cmd, i_pipe) || dup_stdout(cmd, o_pipe))
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		exec_builtin(cmd);
		exit(EXIT_SUCCESS);
	}
	cmds = lst_to_str_arr(cmd->args);
	exec(cmds);
}
