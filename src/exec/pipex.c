/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:23:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/28 14:30:55 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int fds[2])
{
	if (fds)
	{
		close(fds[PIPE_WRITE]);
		close(fds[PIPE_READ]);
	}
}

void	wait_status(void)
{
	int	w_status;

	wait(&w_status);
	if (WIFEXITED(w_status))
		g_exit_code = WEXITSTATUS(w_status);
}

void	pipex(t_list *lst, int i_pipe[2], t_shell *shell)
{
	int		o_pipe[2];
	int		pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)lst->content;
	if (cmd->con == con_PIPE)
		if (pipe(o_pipe) == -1)
			return ((void)b_exec_error("pipe", shell, i_pipe, NULL));
	if (is_tok((char *)cmd->args->content, "cd:export:unset:exit", ':'))
		exec_builtin(cmd, shell);
	else
	{
		pid = fork();
		if (pid == -1)
			return ((void)b_exec_error("fork", shell, i_pipe, o_pipe));
		if (!pid)
			child(cmd, i_pipe, o_pipe, shell);
	}
	close_pipe(i_pipe);
	if (cmd->con == con_PIPE)
		pipex(lst->next, o_pipe, shell);
	wait_status();
}
