/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/17 15:08:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection(t_cmd *cmd, char *arg, char *con)
{
	char	*arg_cpy;

	if (!*arg)
		return (true);
	arg_cpy = str_n_dup(arg, str_len(arg));
	if (!arg_cpy)
		return (true);
	if (!str_cmp("<<", con))
		lst_add_back(&cmd->limiters, lst_new(str_n_dup(arg, str_len(arg))));
	else if (!str_cmp(">>", con) || !str_cmp(">", con))
	{
		lst_add_back(&cmd->outfiles, lst_new(str_n_dup(arg, str_len(arg))));
		cmd->append = false;
		if (!str_cmp(">>", con))
			cmd->append = true;
	}
	else if (!str_cmp("<", con))
		cmd->infile = str_n_dup(arg, str_len(arg));
	if (errno == ENOMEM)
	{
		free(arg);
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
	if (arg && *arg)
		lst_add_back(&cmd->args, lst_new(str_n_dup(arg, str_len(arg))));
	return (false);
}
