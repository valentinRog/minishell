/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:36:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/07 20:13:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirection(t_cmd *cmd, char *arg)
{
	if (!str_n_cmp("<<", arg, str_len("<<")))
	{
		if (str_len(arg) == str_len("<<"))
			return (true);
		if (cmd->limiter)
			free(cmd->limiter);
		cmd->limiter = str_n_dup(arg + str_len("<<"), str_len(arg) - str_len("<<"));
	}
	return (false);
}