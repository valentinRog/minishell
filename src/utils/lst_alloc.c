/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:07:50 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/28 19:08:34 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lst_new(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_clear(t_list **lst, void (*del)(void*))
{
	t_list	*swap;

	while (lst && del && *lst)
	{
		swap = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = swap;
	}
}
