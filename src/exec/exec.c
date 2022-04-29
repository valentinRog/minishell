/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/29 23:37:14 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_shell *shell)
{
	t_list	*node;
	char	**paths;

	node = table_find(shell->table, "PATH");
	if (!node)
	{
		put_str_fd(EMPTY_PATH, STDERR_FILENO);
		return (NULL);
	}
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

t_list	*get_full_cmds(char **cmds, char **paths)
{
	t_list	*lst;
	char	*cmd;

	lst = NULL;
	if (**cmds == '/' || !str_n_cmp(*cmds, "./", 2))
	{
		cmd = str_dup(*cmds);
		if (cmd)
			lst_add_back(&lst, lst_new(cmd));
		if (errno == ENOMEM)
			return (error(&lst, NULL, NULL, cmd));
	}
	while (**cmds != '/' && str_n_cmp(*cmds, "./", 2) && *paths)
	{
		cmd = str_dup(*cmds);
		str_n_insert(&cmd, "/", 0, 1);
		str_n_insert(&cmd, *paths, 0, str_len(*paths));
		if (!cmd)
			return (error(&lst, NULL, NULL, cmd));
		lst_add_back(&lst, lst_new(cmd));
		if (errno == ENOMEM)
			return (error(&lst, NULL, NULL, cmd));
		paths++;
	}
	return (lst);
}

void	exec_bin(char **cmds, t_shell *shell)
{
	char		**paths;
	t_list		*lst;
	char		**env;
	t_list		*node;

	paths = get_paths(shell);
	lst = get_full_cmds(cmds, paths);
	env = get_full_env(shell->table);
	if (!paths || !lst || !env)
	{
		error(&lst, paths, env, NULL);
		e_exec_error("exec_bin", shell);
	}
	node = lst;
	while (node)
	{
		execve(node->content, cmds, env);
		node = node->next;
	}
	b_exec_error(*cmds, shell, NULL, NULL);
	error(&lst, paths, env, NULL);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

bool	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	**cmds;
	bool	err;

	err = false;
	if (!str_cmp((char *)cmd->args->content, "exit"))
		bi_exit(shell);
	if (!str_cmp((char *)cmd->args->content, "pwd") && bi_pwd())
		return (bi_pwd());
	else if (!str_cmp((char *)cmd->args->content, "env"))
		return (bi_env(shell));
	cmds = lst_to_str_arr(cmd->args);
	if (!cmds)
		return (b_exec_error("exec_builtin", NULL, NULL, NULL));
	if (!str_cmp((char *)cmd->args->content, "echo"))
		err = bi_echo(cmds);
	else if (!str_cmp((char *)cmd->args->content, "cd"))
		err = bi_cd(cmds, shell);
	else if (!str_cmp((char *)cmd->args->content, "export"))
		err = bi_export(cmds, shell);
	else if (!str_cmp((char *)cmd->args->content, "unset"))
		err = bi_unset(cmds, shell);
	str_arr_free(cmds);
	return (err);
}
