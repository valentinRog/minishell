/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:56:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 13:41:53 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(int fds[2])
{
	write(fds[PIPE_WRITE], "salut\n", str_len("salut\n"));
	exit(EXIT_SUCCESS);
}

bool	heredoc(t_cmd *cmd)
{
	int	fds[2];
	int	pid;
	int	exit_code;
	int	ret;

	if (pipe(fds) == -1)
		return (b_perror("pipe"));
	pid = fork();
	if (pid == -1)
	{
		close_pipe(fds);
		return (b_perror("fork"));
	}
	if (!pid)
		heredoc_child(fds);
	wait(&exit_code);
	if (!exit_code)
		ret = dup2(fds[PIPE_READ], STDIN_FILENO);
	close_pipe(fds);
	return ((bool)(exit_code || ret));
}
