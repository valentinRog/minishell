/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 10:19:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_con	get_con(char *sep)
{
	if (sep)
	{
		if (!strcmp("||", sep))
			return (con_OR);
		if (!strcmp("&&", sep))
			return (con_AND);
		if (!strcmp("|", sep))
			return (con_PIPE);
	}
	return (con_NONE);
}

bool	redirection(t_cmd *cmd, char *arg, char *con)
{
	char	*arg_cpy;

	arg_cpy = str_dup(arg);
	if (!str_cmp("<<", con) || !str_cmp("<", con))
	{
		safe_free(cmd->infile);
		safe_free(cmd->heredoc);
		if (!str_cmp("<<", con))
			cmd->heredoc = arg_cpy;
		else
			cmd->infile = arg_cpy;
	}
	else if (!str_cmp(">>", con) || !str_cmp(">", con))
	{
		lst_add_back(&cmd->outfiles, lst_new(arg_cpy));
		cmd->append = false;
		if (!str_cmp(">>", con))
			cmd->append = true;
	}
	if (!*arg || errno == ENOMEM)
		return (true);
	return (false);
}

int	z_index(enum e_z z)
{
	static int	z_index;

	if (z == z_INCR)
		z_index++;
	else if (z == z_DECR)
		z_index--;
	else if (z == z_RESET)
		z_index = 0;
	return (z_index);
}

bool	parenthesis(t_cmd *cmd, char *arg, char *con)
{
	if (!str_cmp("(", con))
	{
		if (cmd->args || cmd->heredoc || cmd->outfiles || cmd->infile)
			return (true);
		z_index(z_INCR);
	}
	if (!str_cmp(")", con))
	{
		z_index(z_DECR);
		if (arg && *arg)
			return (true);
	}
	else
		cmd->z_index = z_index(z_NONE);
	return (false);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	if (parenthesis(cmd, arg, con))
		return (true);
	if (is_tok(con, "<<:>>:<:>", ':'))
		return (redirection(cmd, arg, con));
	if (arg && *arg)
		lst_add_back(&cmd->args, lst_new(str_dup(arg)));
	return (false);
}
