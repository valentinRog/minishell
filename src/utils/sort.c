/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:09:58 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/21 09:46:40 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_sort(t_list *lst, int (*cmp)(void *, void *))
{
	bool	swapped;
	t_list	*node;

	swapped = true;
	while (swapped)
	{
		swapped = false;
		node = lst;
		while (node->next)
		{
			if (cmp(node->content, node->next->content) > 0)
			{
				swap_ptr(&node->content, &node->next->content);
				swapped = true;
			}
			node = node->next;
		}
	}
}
