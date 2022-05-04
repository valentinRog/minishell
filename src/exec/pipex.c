/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:23:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 11:28:48 by bvernimm         ###   ########.fr       */
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

static void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2], t_shell *shell)
{
	char	**cmds;

	if (substitute(cmd, shell))
		e_exec_error("substitute", shell);
	if (dup_stdin(cmd, i_pipe, shell) || dup_stdout(cmd, o_pipe))
		e_exec_error(NULL, shell);
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		if (exec_builtin(cmd, shell))
			e_exec_error(cmd->args->content, shell);
		exit(EXIT_SUCCESS);
	}
	cmds = lst_to_str_arr(cmd->args);
	if (!cmds)
		e_exec_error("lst_to_str_arr", shell);
	exec_bin(cmds, shell);
}

void	pipex(t_list *lst, int i_pipe[2], t_shell *shell)
{
	int		o_pipe[2];
	int		pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)lst->content;
	signal(SIGINT, ctrl_c);
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
