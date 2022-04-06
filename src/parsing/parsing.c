/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 12:36:58 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_into_lst(t_list **alst, const char *line)
{
	char	*connector;
	char	*cmd_line;
	t_list	*new_node;
	t_list	*cmd;

	//connector = str_tok(&cmd_line, line, get_connector_arr(), QUOTES);
	if (cmd_line)
	{
		cmd = malloc(sizeof(cmd));
		init_cmd(&cmd);
		//parse_cmd(cmd, cmd_line);
		new_node = lst_new(cmd);
		lst_add_back(alst, new_node);				
	}
	if (connector)
		parse_into_lst(alst, line);
}
