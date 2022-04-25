/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:46:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/25 10:14:43 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	free(var->key);
	free(var->data);
	free(var);
}

t_var	*str_to_var(char *str)
{
	t_var	*var;
	char	*ptr;

	var = malloc(sizeof(t_var));
	if (var)
	{
		ptr = str_chr(str, '=');
		var->key = str_n_dup(str, ptr - str);
		if (!var->key)
		{
			free(var);
			return (NULL);
		}
		var->data = str_dup(ptr + 1);
		if (!var->data)
		{
			free(var->key);
			free(var);
			return (NULL);
		}
	}
	return (var);
}

void	init_env(t_list *table[TABLE_SIZE], char **env)
{
	t_var	*var;

	table_init(table);
	while (*env)
	{
		var = str_to_var(*env);
		if (!var)
			return (table_clear(table, del_var));
		if (!table_add(table, var))
		{
			del_var(var);
			return (table_clear(table, del_var));
		}
		env++;
	}
}

t_list	**get_table(t_list **new_table)
{
	static t_list	**table;

	if (new_table)
		table = new_table;
	return (table);
}
