/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:36:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/11 09:38:05 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_cmd *cmd, char *arg)
{
	char	*str;

	if (!str_n_cmp(arg, HEREDOC, str_len(HEREDOC)))
		str_arr_add(&cmd->limiters, str_n_dup(arg + str_len(HEREDOC), str_len(arg)));
	else if (!str_n_cmp(arg, INFILE, str_len(INFILE)))
		cmd->infile = str_n_dup(arg + str_len(INFILE), str_len(arg));
	else if (!str_n_cmp(arg, APPEND, str_len(APPEND)))
	{
		str_arr_add(&cmd->outfiles, str_n_dup(arg + str_len(APPEND), str_len(arg)));
		cmd->append = true;
	}
	else if (!str_n_cmp(arg, OUTFILE, str_len(OUTFILE)))
	{
		str_arr_add(&cmd->outfiles, str_n_dup(arg + str_len(OUTFILE), str_len(arg)));
		cmd->append = false;
	}
}