/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:20:37 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 12:52:14 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_unset(char **cmds, t_shell *shell)
{
	size_t	i;

	if (str_n_cmp(cmds[0], "unset", str_len(cmds[0])))
		return (true);
	i = 1;
	while (cmds[i])
	{
		table_remove(shell->table, cmds[i]);
		i++;
	}
	return (false);
}
