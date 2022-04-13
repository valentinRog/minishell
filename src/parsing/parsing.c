/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 20:00:36 by vrogiste         ###   ########.fr       */
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

t_list	*get_parsed_lst(char *line)
{
	t_list	*lst;
	t_cmd	*cmd;
	char	*arg;
	char	*con;
	t_tok	tok;

	lst = NULL;
	tok.seps = split(">>:<<:<:>:&&:||:|", ':');
	tok.quotes = QUOTES;
	tok.spaces = SPACES;
	cmd = new_cmd();
	while (true)
	{
		arg = str_tok(&con, line, &tok);
		if (get_con(con))
		{
			cmd->con = get_con(con);
			lst_add_back(&lst, lst_new(cmd));
			cmd = new_cmd();
		}
		if (parse_arg(cmd, arg, con))
			break ;
	}
	lst_add_back(&lst, lst_new(cmd));
	str_tok(NULL, NULL, NULL);
	return (lst);
}
