/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:49:40 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/05 20:28:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_export(char **cmd, t_shell *shell)
{
	t_var	*new_var;
	int		i;

	if (str_cmp(cmd[0], "export"))
		return (true);
	i = 1;
	while (cmd[i])
	{
		new_var = str_to_var(cmd[i]);
		if (errno == ENOMEM)
			return (b_exec_error("export", NULL, NULL, NULL));
		i++;
		if (!new_var)
			continue ;
		if (table_find(shell->table, new_var->key))
			table_remove(shell->table, new_var->key);
		table_add(shell->table, new_var);
		if (errno == ENOMEM)
		{
			del_var((void *)new_var);
			return (b_exec_error("export", NULL, NULL, NULL));
		}
	}
	return (false);
}
