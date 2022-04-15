/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/15 05:31:05 by vrogiste         ###   ########.fr       */
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

bool	parentesis(t_cmd *cmd, char *arg, char *con)
{
	static int	z_index;

	if (!str_cmp("(", con))
		z_index++;
	else if (!str_cmp(")", con))
		z_index--;
	cmd->z_index = z_index;
	return (true);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	if (is_tok(con, "<<:>>:<:>", ':'))
		return (redirection(cmd, arg, con));
	if (is_tok(con, "(:)", ':'))
		return (parentesis(cmd, arg, con));
	return (false);
}
