/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 18:18:18 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **cmds, t_shell *shell)
{
	char	**paths;
	char	*cmd;

	paths = split(((t_var *)table_find(shell->table, "PATH")->content)->data, ':');
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

bool	exec_builtin(t_cmd *cmd)
{
	char	*str;
	char	**cmds;

	str = (char *)cmd->args->content;
	cmds = lst_to_str_arr(cmd->args);
	if (!str_cmp(str, "echo"))
		bi_echo(cmds);
	else if (!str_cmp(str, "cd"))
		bi_cd(cmds);
	else if (!str_cmp(str, "pwd"))
		bi_pwd();
	else if (!str_cmp(str, "export"))
		bi_export(cmds, get_table(NULL));
	else if (!str_cmp(str, "unset"))
		bi_unset(cmds, get_table(NULL));
	else if (!str_cmp(str, "env"))
		bi_env(get_table(NULL));
	else if (!str_cmp(str, "exit"))
		bi_exit();
	str_arr_free(cmds);
	return (false);
}
