/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:43:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/14 17:02:32 by vrogiste         ###   ########.fr       */
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
		str_arr_add(&cmd->limiters, strdup(arg));
		cmd->append = true;
	}
	else if (!str_cmp("<", con))
		cmd->infile = strdup(arg);
	else if (!str_cmp(">", con))
	{
		str_arr_add(&cmd->limiters, strdup(arg));
		cmd->append = false;
	}
	return (false);
}

bool	parse_arg(t_cmd *cmd, char *arg, char *con)
{
	char	**seps;
	bool	error;

	error = false;
	seps = split("<<:>>:<:>", ':');
	if (in_str_arr(con, seps))
		error = redirection(cmd, arg, con);
	str_arr_free(seps);
	return (error);
}
