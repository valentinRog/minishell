/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 05:13:07 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_cmd(char *str)
{
	bool		error;
	t_cmd		*cmd;
	static int	z_index;

	error = false;
	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	cmd->exec_args = ft_split(str, WHITESPACE);
	if (!cmd->exec_args)
		error = true;
	if (error)
	{
		del_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

bool	parse(t_list **alst, const char *line)
{
	char	*ptr;
	t_list	*new_node;
	t_cmd	*content;
	char	*cmd_str;

	ptr = (char *)line;
	while (*ptr && !is_in_str(*ptr, CONNECTORS))
		ptr++;
	while (is_in_str(*ptr, CONNECTORS))
		ptr++;
	cmd_str = ft_strndup(line, ptr - line);
	if (!cmd_str)
		return (true);
	content = parse_cmd(cmd_str);
	new_node = lst_new(content);
	if (!new_node || !content)
	{
		del_cmd(content);
		return (true);
	}
	lst_add_back(alst, new_node);
	if (*ptr)
		return (parse(alst, ptr));	
	return (false);
}
