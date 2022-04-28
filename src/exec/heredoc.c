/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:56:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/28 14:36:54 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(t_cmd *cmd, int fds[2], t_shell *shell)
{
	char	*line;

	line = NULL;
	while (true)
	{
		if (line)
			free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			b_exec_error("get_next_line", shell, fds, NULL);
			exit(EXIT_FAILURE);
		}
		if
			(
			str_len(line) > 1
			&& !str_n_cmp(cmd->heredoc, line, str_len(line) - 1)
			)
				break ;
		write(fds[PIPE_WRITE], line, str_len(line));
	}
	free(line);
	close_pipe(fds);
	clear_shell(shell);
	exit(EXIT_SUCCESS);
}

bool	heredoc(t_cmd *cmd, t_shell *shell)
{
	int	fds[2];
	int	pid;
	int	exit_code;

	if (pipe(fds) < 0)
		return (b_exec_error("pipe", NULL, NULL, NULL));
	pid = fork();
	if (pid < 0)
		return (b_exec_error("fork", NULL, fds, NULL));
	if (!pid)
		heredoc_child(cmd, fds, shell);
	wait(&exit_code);
	if (!exit_code)
		if (dup2(fds[PIPE_READ], STDIN_FILENO) < 0)
			return (b_exec_error("dup2", NULL, fds, NULL));
	close_pipe(fds);
	return (false);
}
