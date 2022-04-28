/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:37:31 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 10:02:44 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_cd(char **cmds)
{
	char	*path;
	char	*user;

	if (str_n_cmp(cmds[0], "cd", str_len(cmds[0])) != 0)
		return ;
	if (cmds[1])
	{
		path = getcwd(NULL, 0);
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmds[1], str_len(path), str_len(cmds[1]));
		if (errno == ENOMEM)
			return ;
	}
	else
	{
		path = str_dup("/Users/");
		user = getenv("USER");
		str_n_insert(&path, user, str_len(path), str_len(user));
		if (errno == ENOMEM)
			return ;
	}
	chdir(path);
	free (path);
}
