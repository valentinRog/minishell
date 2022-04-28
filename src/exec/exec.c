/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/28 14:28:33 by vrogiste         ###   ########.fr       */
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
		exec_error(NULL, shell, NULL, NULL);
		write(2, "PATH not found\n", str_len("PATH not found\n"));
		exit(EXIT_FAILURE);
	}
	paths = split(((t_var *)node->content)->data, ':');
	if (!paths)
	{
		exec_error("split", shell, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	return (paths);
}

void	exec_bin(char **cmds, t_shell *shell)
{
	char		**paths;
	char		*cmd;
	size_t		i;

	paths = get_paths(shell);
	i = 0;
	while (paths[i])
	{
		cmd = str_dup(*cmds);
		str_n_insert(&cmd, "/", 0, 1);
		str_n_insert(&cmd, paths[i], 0, str_len(paths[i]));
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				execve(cmd, cmds, NULL);
			exec_error(cmd, shell, NULL, NULL);
			exit(126);
		}
		i++;
	}
	exec_error(*cmds, shell, NULL, NULL);
	str_arr_free(paths);
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
		return (exec_error("exec_builtin", NULL, NULL, NULL));
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
