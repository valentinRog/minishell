/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:36:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/07 22:57:50 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_file(char **astr, char *arg, char *id)
{
	size_t	id_len;

	id_len = str_len(id);
	if (!str_n_cmp(id, arg, id_len))
	{
		if (str_len(arg) == id_len)
			return (true);
		*astr = str_n_dup(arg + id_len, str_len(arg) - id_len);
	}
	return (false);
}

bool	redirection(t_cmd *cmd, char *arg)
{
	char	*str;

	str = NULL;
	if (get_file(&str, arg, "<<"))
		return (true);
	if (str)
	{
		if (cmd->limiter)
			free(cmd->limiter);
		cmd->limiter = str;
	}
	if (get_file(&str, arg, ">"))
		return (true);
	if (str)
		str_arr_add(&cmd->outfiles, str);
	str = NULL;
	if (get_file(&str, arg, ">>"))
		return (true);
	if (str)
		str_arr_add(&cmd->append_files, str);
	str = NULL;
	if (get_file(&str, arg, "<"))
		return (true);
	if (str)
		str_arr_add(&cmd->infiles, str);
	return (false);
}