/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 22:25:06 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_new_args(t_list *lst, t_shell *shell, t_list *dir_list)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		lst_append_lst(&new_lst, get_match_lst(lst->content, shell, dir_list));
		lst = lst->next;
	}
	return (new_lst);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	t_list	*new_lst;
	t_list	*dir_list;

	dir_list = get_dir_list();
	new_lst = get_new_args(cmd->args, shell, dir_list);
	lst_clear(&cmd->args, free);
	cmd->args = new_lst;
	lst_clear(&dir_list, free);
	return ((bool)(errno == ENOMEM));
}
