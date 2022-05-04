/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:51:12 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/03 12:52:57 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_lst_str(char *str)
{
	char	*content;
	t_list	*new_node;

	content = str_dup(str);
	if (!content)
		return (NULL);
	new_node = lst_new(content);
	if (!new_node)
		free(content);
	return (new_node);
}
