/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/08 13:33:18 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd(t_list **alst, char *cmd_line, char *con)
{
	t_list	*new_node;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	if (!cmd || parse_cmd(cmd, cmd_line, con))
	{
		del_cmd(cmd);
		return (lst_clear(alst, del_cmd));
	}
	new_node = lst_new(cmd);
	if (!new_node)
	{
		del_cmd(cmd);
		return (lst_clear(alst, del_cmd));
	}
	lst_add_back(alst, new_node);
}

static void	clear_parsing(t_list **alst, char **cons, char *con, char *cmd_line)
{
	lst_clear(alst, del_cmd);
	str_arr_free(cons);
	if (con)
		free(con);
	if (cmd_line)
		free(cmd_line);
	str_tok(NULL, NULL, NULL, NULL);
}

void	parse_into_lst(t_list **alst, char *line)
{
	char	*con;
	char	*cmd_line;
	t_list	*new_node;
	t_list	*cmd;
	char	**cons;

	cmd_line = NULL;
	con = NULL;
	cons = split("||:&&:|", ':');
	if (!cons)
		return (clear_parsing(alst, cons, con, cmd_line));
	con = str_tok(&cmd_line, line, cons, QUOTES);
	if (!cmd_line)
		return (clear_parsing(alst, cons, con, cmd_line));
	append_cmd(alst, cmd_line, con);
	free(cmd_line);
	if (con && *alst)
		return (parse_into_lst(alst, line));
	str_tok(NULL, NULL, NULL, NULL);
}
