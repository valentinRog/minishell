/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 04:42:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 05:06:05 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_exec(t_exec *exec)
{
	if (exec)
		del_cmd(exec->cmd);
}

t_list	*get_exec_lst(t_list *parsed_lst)
{
	t_list	*lst;
	t_list	*node;
	t_exec	*exec;

	lst = NULL;
	node = parsed_lst;
	while (node)
	{
		exec = malloc(sizeof(t_exec));
		if (!exec)
		{
			lst_clear(&lst, free);
			return (NULL);
		}
		exec->cmd = node->content;
		lst_add_back(&lst, lst_new(exec));
		if (errno == ENOMEM)
		{
			lst_clear(&lst, free);
			return (NULL);
		}
		node = node->next;
	}
	return (lst);
}
