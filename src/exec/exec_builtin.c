/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:39:38 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/25 18:47:16 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
