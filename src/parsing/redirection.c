/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:36:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/08 19:18:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_con(char *str)
{
	if (!str_n_cmp(str, APPEND, str_len(APPEND)))
		return (APPEND);
	if (!str_n_cmp(str, HEREDOC, str_len(HEREDOC)))
		return (HEREDOC);
	if (!str_n_cmp(str, INFILE, str_len(INFILE)))
		return (INFILE);
	if (!str_n_cmp(str, OUTFILE, str_len(OUTFILE)))
		return (OUTFILE);
	return (NULL);
}

bool	redirection(t_cmd *cmd, char *arg)
{
	char	*con;

	con = get_con(arg);
	if (!con)
		return (false);
	if (strlen(con) == str_len(arg))
		return (true);
	if (!str_n_cmp(con, APPEND, str_len(APPEND)))
	{
		str_arr_add(&cmd->outfiles, str_n_dup(arg + str_len(con), str_len(arg)));
		cmd->append = true;
	}
	else if (!str_n_cmp(con, HEREDOC, str_len(HEREDOC)))
		str_arr_add(&cmd->limiters, str_n_dup(arg + str_len(con), str_len(arg)));
	else if (!str_n_cmp(con, INFILE, str_len(INFILE)))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = str_n_dup(arg + str_len(con), str_len(arg));
	}
	else if (!str_n_cmp(con, OUTFILE, str_len(OUTFILE)))
	{
		str_arr_add(&cmd->outfiles, str_n_dup(arg + str_len(con), str_len(arg)));
		cmd->append = false;
	}
	return (false);
}