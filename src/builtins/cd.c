/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:37:31 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/07 11:28:56 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **cmds, t_shell *shell)
{
	char	*path;
	char	*user;
	t_list	*node;

	if (cmds[1])
	{
		path = getcwd(NULL, 0);
		str_n_insert(&path, "/", str_len(path), 1);
		str_n_insert(&path, cmds[1], str_len(path), str_len(cmds[1]));
	}
	else
	{
		node = table_find(shell->table, "USER");
		if (!node)
		{
			put_str_fd(NO_USER, STDERR_FILENO);
			return (NULL);
		}
		path = str_dup("/Users/");
		user = (char *)((t_var *)node->content)->data;
		str_n_insert(&path, user, str_len(path), str_len(user));
	}
	return (path);
}

bool	bi_cd(char **cmds, t_shell *shell)
{
	char	*path;

	if (!cmds || str_cmp("cd", *cmds))
		return (true);
	path = get_path(cmds, shell);
	if (errno == ENOMEM)
		return (b_exec_error("cd", NULL, NULL, NULL));
	if (!path)
		return (true);
	if (chdir(path) < 0)
	{
		perror(path);
		free(path);
		return (true);
	}
	free (path);
	return (false);
}
