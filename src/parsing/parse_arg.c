/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/15 11:58:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection(t_cmd *cmd, char *arg, char *con)
{
	if (!*arg)
		return (true);
	if (!str_cmp("<<", con))
		lst_add_back(&cmd->limiters, lst_new(str_n_dup(arg, str_len(arg))));
	else if (!str_cmp(">>", con))
	{
		lst_add_back(&cmd->outfiles, lst_new(str_n_dup(arg, str_len(arg))));
		cmd->append = true;
	}
	else if (!str_cmp("<", con))
		cmd->infile = str_n_dup(arg, str_len(arg));
	else if (!str_cmp(">", con))
	{
		lst_add_back(&cmd->outfiles, lst_new(str_n_dup(arg, str_len(arg))));
		cmd->append = false;
	}
	return (false);
}

bool	parenthesis(t_cmd *cmd, char *arg, char *con)
{
	if (!str_cmp("(", con))
	{
		if (cmd->args || cmd->limiters || cmd->outfiles || cmd->infile)
			return (true);
		if (*arg)
			lst_add_back(&cmd->args, lst_new(str_n_dup(arg, str_len(arg))));
	}
	else if (!str_cmp(")", con))
	{
		if (arg && *arg)
			return (true);
	}
	return (false);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	if (is_tok(con, "<<:>>:<:>", ':'))
		return (redirection(cmd, arg, con));
	if (parenthesis(cmd, arg, con))
		return (true);
	lst_add_back(&cmd->args, lst_new(str_n_dup(arg, str_len(arg))));
	return (false);
}
