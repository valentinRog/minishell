/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:36:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/08 17:39:07 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_con(char *str)
{
	if (!str_n_cmp(str, INFILE, str_len(INFILE)))
		return (INFILE);
	if (!str_n_cmp(str, OUTFILE, str_len(OUTFILE)))
		return (OUTFILE);
	if (!str_n_cmp(str, APPEND, str_len(APPEND)))
		return (APPEND);
	if (!str_n_cmp(str, HEREDOC, str_len(HEREDOC)))
		return (HEREDOC);
	return (NULL);
}

bool	redirection(t_cmd *cmd, char *arg)
{
	char	*str;

	return (false);
}