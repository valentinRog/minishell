/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:20:37 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 10:18:03 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_unset(char **cmd, t_shell *shell)
{
	char	*var;
	char	*ptr;
	int		i;

	if (str_n_cmp(cmd[0], "unset", str_len(cmd[0])) != 0)
		return (true);
	i = 1;
	while (cmd[i])
	{
		ptr = str_chr(cmd[i], '=');
		var = str_n_dup(cmd[i], ptr - cmd[i]);
		if (errno == ENOMEM)
			return (true);
		if (table_find(shell->table, var))
			table_remove(shell->table, var);
		free (var);
		i++;
	}
	return (false);
}
