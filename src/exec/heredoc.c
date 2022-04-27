/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:56:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 15:29:40 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(t_cmd *cmd, int fds[2])
{
	char	*line;

	line = NULL;
	while (true)
	{
		safe_free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_FAILURE);
		if (str_len(line) > 1 && !str_n_cmp(cmd->heredoc, line, str_len(line) - 1))
			break ;
		write(fds[PIPE_WRITE], line, str_len(line));
	}
	free(line);
	close_pipe(fds);
	exit(EXIT_SUCCESS);
}

bool	heredoc(t_cmd *cmd, t_shell *shell)
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
		heredoc_child(cmd, fds);
	wait(&exit_code);
	if (!exit_code)
		ret = dup2(fds[PIPE_READ], STDIN_FILENO);
	close_pipe(fds);
	return ((bool)(exit_code || ret));
}
