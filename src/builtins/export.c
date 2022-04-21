/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:49:40 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/21 16:07:39 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **cmd, t_list *table[TABLE_SIZE])
{
	t_var	*new_var;
	int		i;

	if (str_n_cmp(cmd[0], "export", str_len(cmd[0])) != 0)
		return ;
	i = 1;
	while (cmd[i])
	{
		new_var = str_to_var(cmd[i]);
		if (errno == ENOMEM)
			return ;
		if (table_find(table, new_var->key))
			table_remove(table, new_var->key);
		table_add(table, new_var);
		if (errno == ENOMEM)
			return ;
		i++;
	}
}
