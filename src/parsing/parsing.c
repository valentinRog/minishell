/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 14:36:56 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_args(t_cmd *cmd, char *str)
{
	static int	z_index;

	if (get_limiter(cmd, str))
		return (true);
	if (get_in_out(cmd, str))
		return (true);
	if (get_connector(cmd, str))
		return (true);
	return (false);
}

t_cmd	*parse_cmd(char *str)
{
	bool		error;
	t_cmd		*cmd;

	error = false;
	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	if (parse_args(cmd, str))
	{
		del_cmd(cmd);
		return (NULL);
	}
	cmd->exec_args = ft_split(str, WHITESPACES, QUOTES);
	if (!cmd->exec_args)
		error = true;
	if (error)
	{
		del_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static bool	check_end(t_list *last_node)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)last_node->content;
	if (cmd->connector != END || cmd->z_index)
		return (true);
	return (false);
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
	while (*ptr && is_in_str(*ptr, CONNECTORS))
		ptr++;
	cmd_str = ft_strndup(line, ptr - line);
	if (!cmd_str)
		return (true);
	content = parse_cmd(cmd_str);
	free(cmd_str);
	new_node = lst_new(content);
	if (!new_node || !content)
	{
		del_cmd(content);
		return (true);
	}
	lst_add_back(alst, new_node);
	if (*ptr)
		return (parse(alst, ptr));
	return (check_end(new_node));
}
