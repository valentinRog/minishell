/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 02:48:45 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_cmd(char *str)
{
	printf("%s\n", str);
}

bool	parse(t_list **alst, const char *line)
{
	char	*ptr;

	ptr = (char *)line;
	while (*ptr && !is_in_str(*ptr, CONNECTORS))
		ptr++;
	while (is_in_str(*ptr, CONNECTORS))
		ptr++;
	parse_cmd(ft_strndup(line, ptr - line));
	if (*ptr)
		return parse(alst, ptr);
	return false;
}
