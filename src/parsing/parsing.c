/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/03 17:48:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_args(t_cmd *cmd, char *str)
{
	if (get_connector(cmd, str))
		return (true);
	if (get_z_index(cmd, str))
	{
		z_index(RESET);
		return (true);
	}
	if (get_limiter(cmd, str))
		return (true);
	if (get_in_out(cmd, str))
		return (true);
	return (false);
}

static t_cmd	*parse_cmd(char *str)
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
	int		temp;

	cmd = (t_cmd *)last_node->content;
	temp = z_index(NONE);
	z_index(RESET);
	if (cmd->connector != END || temp)
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
	skip_next_word(&ptr, CONNECTORS, QUOTES);
	skip_charset(&ptr, CONNECTORS);
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
