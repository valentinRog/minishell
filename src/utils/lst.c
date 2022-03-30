/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:06:43 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/28 19:08:43 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_size(t_list *lst)
{
	if (lst)
		return (1 + lst_size(lst->next));
	return (0);
}

t_list	*lst_last(t_list *lst)
{
	if (lst && lst->next)
		return (lst_last(lst->next));
	return (lst);
}

void	lst_add_front(t_list **alst, t_list *new_node)
{
	if (alst && new_node)
	{
		new_node->next = *alst;
		new_node->prev = NULL;
		if (*alst)
			(*alst)->prev = new_node;
		*alst = new_node;
	}
}

void	lst_add_back(t_list **alst, t_list *new_node)
{
	t_list	*last;

	if (alst && new_node)
	{
		if (!*alst)
		{
			*alst = new_node;
			new_node->prev = NULL;
		}
		else
		{
			last = lst_last(*alst);
			last->next = new_node;
			new_node->prev = last;
		}
		new_node->next = NULL;
	}
}
