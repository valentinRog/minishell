/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:21:23 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/03 21:00:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_content(char c)
{
	char	*content;

	content = malloc(sizeof(char));
	if (content)
		*content = c;
	return (content);
}

static char	*lst_to_str(t_list *lst)
{
	t_list	*node;
	size_t	i;
	char	*dst;

	if (!lst)
		return (NULL);
	node = lst;
	i = 1;
	while (node->next && ++i)
		node = node->next;
	dst = malloc((i + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (node)
	{
		dst[i] = *(char *)node->content;
		node = node->prev;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

bool	get_next_line(char **dst, int fd)
{
	t_list	*lst;
	t_list	*new_node;
	char	c;

	lst = NULL;
	c = '\0';
	if (!dst)
		return (false);
	while (c != '\n' && read(fd, &c, 1) > 0)
	{
		new_node = lst_new(get_content(c));
		if (!new_node || !new_node->content)
		{
			lst_clear(&lst, free);
			return (true);
		}
		lst_add_front(&lst, new_node);
	}
	*dst = lst_to_str(lst);
	if (lst && !*dst)
	{
		lst_clear(&lst, free);
		return (true);
	}
	return (false);
}
