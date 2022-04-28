/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:37:31 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 11:37:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **cmds)
{
	char	*path;
	char	*user;

	if (cmds[1])
	{
		path = getcwd(NULL, 0);
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmds[1], str_len(path), str_len(cmds[1]));
	}
	else
	{
		path = str_dup("/Users/");
		user = getenv("USER");
		str_n_insert(&path, user, str_len(path), str_len(user));
	}
	return (path);
}

bool	bi_cd(char **cmds)
{
	char	*path;

	if (!cmds || str_cmp("cd", *cmds))
		return (true);
	path = get_path(cmds);
	if (!path)
		return (exec_error("cd", NULL, NULL, NULL));
	if (chdir(path) < 0)
	{
		perror(path);
		free(path);
		return (true);
	}
	free (path);
	return (false);
}
