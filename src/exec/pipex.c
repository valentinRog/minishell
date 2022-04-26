/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:23:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 11:00:29 by vrogiste         ###   ########.fr       */
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

static void	exec(char **cmds)
{
	char	**paths;
	char	*cmd;

	paths = split(((t_var *)table_find(get_table(NULL), "PATH")->content)->data, ':');
	while (*paths)
	{
		cmd = str_dup(*cmds);
		str_n_insert(&cmd, "/", 0, 1);
		str_n_insert(&cmd, *paths, 0, str_len(*paths));
		execve(cmd, cmds, NULL);
		paths++;
	}
	exit(EXIT_FAILURE);
}

static void	child(t_cmd *cmd, int i_pipe[2], int o_pipe[2])
{
	char	**cmds;

	cmds = lst_to_str_arr(cmd->args);
	if (i_pipe)
	{
		dup2(i_pipe[PIPE_READ], STDIN_FILENO);
		close_pipe(i_pipe);
	}
	if (cmd->con == con_PIPE)
	{
		dup2(o_pipe[PIPE_WRITE], STDOUT_FILENO);
		close_pipe(o_pipe);
	}
	if (is_tok((char *)cmd->args->content, "env:echo:pwd", ':'))
	{
		exec_builtin(cmd, NULL);
		exit(EXIT_SUCCESS);
	}
	exec(cmds);
}

void	wait_status(void)
{
	int	w_status;

	wait(&w_status);
	if (WIFEXITED(w_status))
		g_exit_code = WEXITSTATUS(w_status);
}

void	pipex(t_list *lst, t_list **alst, int i_pipe[2])
{
	int		o_pipe[2];
	int		pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)lst->content;
	if (cmd->con == con_PIPE)
		if (pipe(o_pipe) == -1)
			return (error_pipex("pipe", i_pipe, NULL));
	if (is_tok((char *)cmd->args->content, "cd:export:unset:exit", ':'))
		exec_builtin(cmd, o_pipe);
	else
	{
		pid = fork();
		if (pid == -1)
			return (error_pipex("fork", i_pipe, o_pipe));
		if (!pid)
			child(cmd, i_pipe, o_pipe);
	}
	close_pipe(i_pipe);
	if (cmd->con == con_PIPE)
		pipex(lst->next, alst, o_pipe);
	wait_status();
}
