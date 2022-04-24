/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/24 16:20:23 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_launcher(t_list *lst, int z_index, t_list *table[TABLE_SIZE])
{
	while (lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
	{
		if (((t_exec *)lst->content)->cmd->z_index > z_index)
		{
			exec_launcher(lst, z_index + 1, table);
			while
				(
				lst && lst->next
				&& ((t_exec *)lst->next->content)->cmd->z_index > z_index
				)
				lst = lst->next;
		}
		else
			pipex(lst, table);
		while (((t_exec *)lst->content)->cmd->con == con_PIPE)
			lst = lst->next;
		if
			(
			!lst
			|| g_exit_code && ((t_exec *)lst->content)->cmd->con == con_AND
			|| !g_exit_code && ((t_exec *)lst->content)->cmd->con == con_OR
			)
				break ;
		lst = lst->next;
	}
}
