/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/07 11:26:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_shell *shell)
{
	t_list	*node;
	char	**paths;

	node = table_find(shell->table, "PATH");
	if (!node)
		return (NULL);
	paths = split(((t_var *)node->content)->data, ':');
	return (paths);
}

static void	*error(t_list **alst, char **paths, char **env, char *cmd)
{
	lst_clear(alst, free);
	str_arr_free(paths);
	str_arr_free(env);
	if (cmd)
		free(cmd);
	return (NULL);
}

static t_list	*get_full_cmds(char **cmds, char **paths)
{
	t_list	*lst;
	char	*cmd;

	lst = NULL;
	if (!cmds || !*cmds)
		return (NULL);
	if (**cmds == '/' || !str_n_cmp(*cmds, "./", 2))
	{
		cmd = str_dup(*cmds);
		if (cmd)
			if (!lst_add_back(&lst, lst_new(cmd)))
				return (error(&lst, NULL, NULL, cmd));
	}
	while (**cmds != '/' && str_n_cmp(*cmds, "./", 2) && paths && *paths)
	{
		cmd = str_dup(*cmds);
		str_n_insert(&cmd, "/", 0, 1);
		str_n_insert(&cmd, *paths, 0, str_len(*paths));
		if (!cmd)
			return (error(&lst, NULL, NULL, cmd));
		if (!lst_add_back(&lst, lst_new(cmd)))
			return (error(&lst, NULL, NULL, cmd));
		paths++;
	}
	return (lst);
}

static void	try_execve(t_list *lst, char **cmds, char **env)
{
	t_list	*node;

	node = lst;
	while (node)
	{
		execve(node->content, cmds, env);
		node = node->next;
	}
}

void	exec_bin(char **cmds, t_shell *shell)
{
	char		**paths;
	t_list		*lst;
	char		**env;

	paths = get_paths(shell);
	lst = get_full_cmds(cmds, paths);
	env = get_full_env(shell->table);
	if (errno == ENOMEM)
	{
		error(&lst, paths, env, NULL);
		e_exec_error("exec_bin", shell);
	}
	try_execve(lst, cmds, env);
	b_exec_error(NULL, shell, NULL, NULL);
	error(&lst, paths, env, NULL);
	if (errno == EACCES)
	{
		perror(*cmds);
		exit(126);
	}
	put_str_fd(*cmds, STDERR_FILENO);
	put_str_fd(CMD_NOT_FOUND, STDERR_FILENO);
	exit(127);
}
