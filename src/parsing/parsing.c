/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/02 14:11:23 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_limiter(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "<<");
	if (ptr)
	{
		*ptr = ' ';
		*(ptr + 1) = ' ';
		cmd->limiter = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->limiter)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (false);
}

bool	get_in_out(t_cmd *cmd, char *str)
{
	char	*ptr;

	ptr = strstr(str, "<");
	if (ptr)
	{
		*ptr = ' ';
		cmd->infile = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->infile)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	ptr = strstr(str, ">");
	if (ptr)
	{
		*ptr = ' ';
		if (*(ptr + 1) == '>')
		{
			*(ptr + 1) = ' ';
			cmd->append = true;
		}
		cmd->outfile = get_next_word(ptr, WHITESPACES, QUOTES);
		if (!cmd->outfile)
			return (true);
		delete_next_word(ptr, WHITESPACES, QUOTES);
	}
	return (false);
}

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
