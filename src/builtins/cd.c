/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:37:31 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/21 15:12:53 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd)
{
	char	*path;
	char	*user;

	if (str_n_cmp(cmd[0], "cd", str_len(cmd[0])) != 0)
		return ;
	path = NULL;
	path = getcwd(path, 0);
	if (errno == ENOMEM)
		return ;
	if (cmd[1])
	{
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmd[1], str_len(path), str_len(cmd[1]));
		if (errno == ENOMEM)
			return ;
		chdir(path);
	}
	else
	{
		path = str_dup("/Users/");
		user = getenv("USER");
		str_n_insert(&path, user, str_len(path), str_len(user));
		chdir(path);
	}
	free (path);
}
