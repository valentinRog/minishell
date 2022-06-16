/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/06/16 17:22:30 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*skip_higher_z(t_list *lst, int z)
{
	if (lst && lst->next && ((t_cmd *)lst->next->content)->z_index > z)
		return (skip_higher_z(lst->next, z));
	return (lst);
}

void	launcher(t_list *lst, int z, t_shell *shell)
{
	while (lst && ((t_cmd *)lst->content)->z_index >= z)
	{
		if (((t_cmd *)lst->content)->z_index > z)
		{
			launcher(lst, z + 1, shell);
			lst = skip_higher_z(lst, z);
		}
		else
			pipex(lst, NULL, shell);
		while (((t_cmd *)lst->content)->con == con_PIPE)
			lst = lst->next;
		while (lst && g_exit_code && ((t_cmd *)lst->content)->con == con_AND)
			lst = skip_higher_z(lst->next, z);
		while (lst && (!g_exit_code && ((t_cmd *)lst->content)->con == con_OR))
			lst = skip_higher_z(lst->next, z);
		lst = lst->next;
	}
}
