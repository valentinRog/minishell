/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:50:15 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 09:53:30 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	dup_stdin(t_cmd *cmd, int i_pipe[2])
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
			return (b_perror(cmd->infile));
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i_pipe)
		ret = dup2(i_pipe[PIPE_READ], STDIN_FILENO);
	close_pipe(i_pipe);
	if (ret == -1)
		return (b_perror("dup2"));
	return (false);
}

static bool	dup_outfile(t_cmd *cmd, int o_pipe[2])
{
	t_list	*node;
	int		fd;
	int		ret;

	node = cmd->outfiles;
	while (node)
	{
		fd = open((char *)node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
		{
			if (cmd->con == con_PIPE)
				close_pipe(o_pipe);
			return (b_perror((char *)node->content));
		}
		if (node->next)
			close(fd);
		node = node->next;
	}
	ret = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (cmd->con == con_PIPE)
		close_pipe(o_pipe);
	if (ret == -1)
		return (b_perror("dup2"));
	return (false);
}

bool	dup_stdout(t_cmd *cmd, int o_pipe[2])
{
	int	ret;

	if (cmd->outfiles)
	{
		if (dup_outfile(cmd, o_pipe))
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
