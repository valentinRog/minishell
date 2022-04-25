/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:23:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/25 15:52:02 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(i_pipe[PIPE_WRITE]);
		close(i_pipe[PIPE_READ]);
	}
	if (cmd->con == con_PIPE)
	{
		dup2(o_pipe[PIPE_WRITE], STDOUT_FILENO);
		close(o_pipe[PIPE_WRITE]);
		close(o_pipe[PIPE_READ]);
	}
	exec(cmds);
}

void	pipex(t_list *lst, t_list **alst, int i_pipe[2])
{
	int		o_pipe[2];
	int		pid;

	if (((t_cmd *)lst->content)->con == con_PIPE)
		if (pipe(o_pipe) == -1)
			return (error_pipex("pipe", i_pipe, NULL));
	if (is_tok((char *)((t_cmd *)lst->content)->args->content, BUILTINS, ':'))
		exec_builtin();
	else
	{
		pid = fork();
		if (pid == -1)
			return (error_pipex("fork", i_pipe, o_pipe));
		if (!pid)
			child((t_cmd *)lst->content, i_pipe, o_pipe);
	}
	if (i_pipe)
	{
		close(i_pipe[PIPE_WRITE]);
		close(i_pipe[PIPE_READ]);
	}
	if (((t_cmd *)lst->content)->con == con_PIPE)
		pipex(lst->next, alst, o_pipe);
	wait(NULL);
}
