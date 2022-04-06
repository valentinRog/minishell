/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 16:18:01 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cmd(t_cmd *cmd, char *cmd_line, char *con)
{
	printf("%s\n", cmd_line);
}

void	append_cmd(t_list **alst, char *cmd_line, char *con)
{
	t_list	*new_node;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd);
	parse_cmd(cmd, cmd_line, con);
	new_node = lst_new(cmd);
	if (!new_node || !cmd)
	{
		del_cmd(cmd);
		if (new_node)
			free(new_node);
		lst_clear(alst, del_cmd);
		if (!cmd)
			free(con);
		return ;
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
