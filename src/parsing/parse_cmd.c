/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:15:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/11 09:58:07 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_parse_loop(t_cmd *cmd, char *cmd_line)
{
	char	*arg;

	arg = str_tok_simple(cmd_line, ' ', QUOTES);
	if (arg)
	{
		redirection(cmd, arg);
		if (errno != ENOMEM)
			return (cmd_parse_loop(cmd, cmd_line));
	}
	str_tok_simple(NULL, '\0', NULL);
}

void	parse_cmd(t_cmd *cmd, char *cmd_line, char *con)
{
	char	*cmd_line_cpy;

	if (cmd)
	{
		cmd_line_cpy = str_n_dup(cmd_line, str_len(cmd_line));
		if (!cmd_line_cpy)
		{
			free(con);
			return ;
		}
		cmd->connector = con;
		format(&cmd_line_cpy);
		if (!cmd_line_cpy)
			return ;
		cmd_parse_loop(cmd, cmd_line_cpy);
		free(cmd_line_cpy);
	}
}
