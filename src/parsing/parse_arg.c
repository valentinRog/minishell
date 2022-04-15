/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/15 03:07:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection(t_cmd *cmd, char *arg, char *con)
{
	if (!*arg)
		return (true);
	if (!str_cmp("<<", con))
		str_arr_add(&cmd->limiters, strdup(arg));
	else if (!str_cmp(">>", con))
	{
		str_arr_add(&cmd->outfiles, strdup(arg));
		cmd->append = true;
	}
	else if (!str_cmp("<", con))
		cmd->infile = strdup(arg);
	else if (!str_cmp(">", con))
	{
		str_arr_add(&cmd->outfiles, strdup(arg));
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
