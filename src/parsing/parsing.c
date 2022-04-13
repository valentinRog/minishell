/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 22:57:54 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_con(t_cmd *cmd, char *arg, char *con)
{
	cmd->con = get_con(con);
}
	

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	if (!arg)
		return (true);
	return (false);
}

static void	clear_parsing(t_list **alst, t_cmd *cmd, char *arg, char *con)
{
	lst_clear(alst, del_cmd);
	del_cmd(cmd);
	if (arg)
		free(arg);
	if (con)
		free(con);
	str_tok(NULL, NULL, NULL);
}

static void	parse_into_lst(t_list **alst, char *line, t_tok *tok)
{
	t_cmd	*cmd;
	char	*arg;
	char	*con;

	new_cmd(&cmd);
	while (true)
	{
		arg = str_tok(&con, line, tok);
		if (get_con(con))
		{
			cmd->con = get_con(con);
			lst_add_back(alst, lst_new(cmd));
			cmd = new_cmd(NULL);
		}
		if (!arg)
			break ;
		parse_arg(cmd, arg, con);
		free(arg);
	}
	lst_add_back(alst, lst_new(cmd));
	str_tok(NULL, NULL, NULL);
}

t_list	*get_parsed_lst(char *line)
{
	t_list	*lst;
	t_tok	tok;

	lst = NULL;
	tok.seps = split(">>:<<:<:>:&&:||:|", ':');
	if (!tok.seps)
		return (NULL);
	tok.quotes = QUOTES;
	tok.spaces = SPACES;
	parse_into_lst(&lst, line, &tok);
	str_arr_free(tok.seps);
	return (lst);
}
