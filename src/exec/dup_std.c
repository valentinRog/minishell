/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:50:15 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/28 10:37:23 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	dup_stdin(t_cmd *cmd, int i_pipe[2], t_shell *shell)
{
	int	fd;

	if (cmd->heredoc)
		return (heredoc(cmd, shell));
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			return (exec_error(cmd->infile, NULL, i_pipe, NULL));
		if (dup2(fd, STDIN_FILENO) < 0 || close(fd))
			return (exec_error("dup2", NULL, i_pipe, NULL));
	}
	else if (i_pipe)
		if (dup2(i_pipe[PIPE_READ], STDIN_FILENO) < 0)
			return (exec_error("dup2", NULL, i_pipe, NULL));
	close_pipe(i_pipe);
	return (false);
}

static bool	dup_outfile(t_cmd *cmd, int o_pipe[2])
{
	t_list	*node;
	int		fd;

	node = cmd->outfiles;
	while (node)
	{
		if (cmd->append)
			fd = open((char *)node->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd = open((char *)node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			return (exec_error((char *)node->content, NULL, NULL, o_pipe));
		if (node->next)
			close(fd);
		node = node->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1 || close(fd))
		return (exec_error("dup2", NULL, NULL, o_pipe));
	close_pipe(o_pipe);
	return (false);
}

bool	dup_stdout(t_cmd *cmd, int o_pipe[2])
{
	int	*ptr;

	ptr = NULL;
	if (cmd->con == con_PIPE)
		ptr = o_pipe;
	if (cmd->outfiles)
	{
		if (dup_outfile(cmd, ptr))
			return (true);
	}
	else if (cmd->con == con_PIPE)
		if (dup2(ptr[PIPE_WRITE], STDOUT_FILENO) < 0)
			return (exec_error("dup2", NULL, NULL, ptr));
	close_pipe(ptr);
	return (false);
}
