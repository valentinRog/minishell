/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:37:31 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/26 14:50:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_cd(char **cmd)
{
	char	*path;
	char	*user;

	if (str_n_cmp(cmd[0], "cd", str_len(cmd[0])) != 0)
		return ;
	if (cmd[1])
	{
		path = getcwd(NULL, 0);
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmd[1], str_len(path), str_len(cmd[1]));
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
