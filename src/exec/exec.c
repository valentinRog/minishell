/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:45:34 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 12:49:27 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char **cmds)
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

void	exec_builtin(t_cmd *cmd, int o_pipe[2])
{
	char	*str;
	char	**cmds;

	str = (char *)cmd->args->content;
	cmds = lst_to_str_arr(cmd->args);
	if (!str_cmp(str, "echo"))
		ft_echo(cmds);
	else if (!str_cmp(str, "cd"))
		ft_cd(cmds);
	else if (!str_cmp(str, "pwd"))
		ft_pwd();
	else if (!str_cmp(str, "export"))
		ft_export(cmds, get_table(NULL));
	else if (!str_cmp(str, "unset"))
		ft_unset(cmds, get_table(NULL));
	else if (!str_cmp(str, "env"))
		ft_env(get_table(NULL));
	else if (!str_cmp(str, "exit"))
		ft_exit();
	str_arr_free(cmds);
}
