/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:07:50 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/21 09:35:05 by bvernimm         ###   ########.fr       */
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

void	lst_del_one(t_list *node, void (*del)(void*))
{
	if (node)
	{
		if (del)
			del(node->content);
		free(node);
	}
}

void	lst_clear(t_list **alst, void (*del)(void*))
{
	t_list	*swap;
	t_list	*node;

	if (!alst)
		return ;
	node = *alst;
	while (node)
	{
		swap = node->next;
		lst_del_one(node, del);
		node = swap;
	}
	*alst = NULL;
}

void	lst_remove(t_list **alst, t_list *node, void (*del)(void*))
{
	if (node && del)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (!node->prev)
			*alst = node->next;
		if (node->next)
			node->next->prev = node->prev;
		lst_del_one(node, del);
	}
}
