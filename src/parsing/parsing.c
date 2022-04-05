/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 15:49:24 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse(t_list **alst, const char *line)
{
}

t_list	*get_parsed_lst(const char *line)
{
	t_list	*lst;

	lst = NULL;
	if (parse(&lst, line))
	{
		lst_clear(&lst, del_cmd);
		return (NULL);
	}
	return (lst);
}
