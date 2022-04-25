/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/25 11:11:20 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launcher(t_list *lst, int z, t_list **alst)
{
	while (lst && ((t_cmd *)lst->content)->z_index >= z)
	{
		if (((t_cmd *)lst->content)->z_index > z)
		{
			launcher(lst, z + 1, alst);
			while
				(
				lst && lst->next
				&& ((t_cmd *)lst->next->content)->z_index > z
				)
				lst = lst->next;
		}
		else
			pipex(lst, alst, NULL);
		while (((t_cmd *)lst->content)->con == con_PIPE)
			lst = lst->next;
		if
			(
			!lst
			|| (g_exit_code && ((t_cmd *)lst->content)->con == con_AND)
			|| (!g_exit_code && ((t_cmd *)lst->content)->con == con_OR)
			)
				break ;
		lst = lst->next;
	}
}
