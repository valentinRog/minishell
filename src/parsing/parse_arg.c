/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/08 08:25:59 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error(char *arg)
{
	if (errno == ENOMEM)
		perror("");
	free(arg);
	return (true);
}

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
	if (!*arg || !arg_cpy)
		return (error(arg_cpy));
	if (!str_cmp("<<", con) || !str_cmp("<", con))
	{
		free(cmd->infile);
		free(cmd->heredoc);
		if (!str_cmp("<<", con))
			cmd->heredoc = arg_cpy;
		else
			cmd->infile = arg_cpy;
	}
	else if (!str_cmp(">>", con) || !str_cmp(">", con))
	{
		if (!lst_add_back(&cmd->outfiles, lst_new(arg_cpy)))
			return (error(arg_cpy));
		cmd->append = false;
		if (!str_cmp(">>", con))
			cmd->append = true;
	}
	else
		free(arg_cpy);
	return (false);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	char	*arg_cpy;

	if (parenthesis(cmd, arg, con))
		return (true);
	if (is_tok(con, "<<:>>:<:>", ':'))
		return (redirection(cmd, arg, con));
	if (arg && *arg)
	{
		arg_cpy = str_dup(arg);
		if (!arg_cpy)
			return (true);
		if (!lst_add_back(&cmd->args, lst_new(arg_cpy)))
			return (error(arg_cpy));
	}
	return (false);
}
