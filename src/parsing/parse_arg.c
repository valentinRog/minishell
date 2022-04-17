/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/17 18:33:29 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection(t_cmd *cmd, char *arg, char *con)
{
	char	*arg_cpy;

	arg_cpy = str_dup(arg);
	if (!arg_cpy)
		return (true);
	if (!str_cmp("<<", con))
		lst_add_back(&cmd->limiters, lst_new(arg_cpy));
	else if (!str_cmp(">>", con) || !str_cmp(">", con))
	{
		lst_add_back(&cmd->outfiles, lst_new(arg_cpy));
		cmd->append = false;
		if (!str_cmp(">>", con))
			cmd->append = true;
	}
	else if (!str_cmp("<", con))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = arg_cpy;
	}
	if (errno != ENOMEM && *arg)
		return (false);
	if (errno == ENOMEM)
		free(arg_cpy);
	return (true);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	if (is_tok(con, "<<:>>:<:>", ':'))
		return (redirection(cmd, arg, con));
	if (parenthesis(cmd, arg, con))
		return (true);
	if (arg && *arg)
		lst_add_back(&cmd->args, lst_new(str_dup(arg)));
	return (false);
}
