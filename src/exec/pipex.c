/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:23:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/24 21:06:51 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_list *lst, t_list	*table[TABLE_SIZE], t_list **alst)
{
	printf("%s\n", (char *)((t_cmd *)lst->content)->args->content);
	if (!str_cmp((char *)((t_cmd *)lst->content)->args->content, "0"))
		g_exit_code = 1;
	else
		g_exit_code = 0;
	if (((t_cmd *)lst->content)->con == con_PIPE)
		pipex(lst->next, table, alst);
}
