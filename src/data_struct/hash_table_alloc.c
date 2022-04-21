/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:11:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/21 15:50:25 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*table_add(t_list *table[TABLE_SIZE], t_var *var)
{
	t_list	*new_node;

	if (table_find(table, var->key))
		return (NULL);
	new_node = lst_new(var);
	lst_add_back(&table[hash(var->key) % TABLE_SIZE], new_node);
	return (new_node);
}

void	table_remove(t_list *table[TABLE_SIZE], char *key)
{
	t_list	*node;

	node = table_find(table, key);
	if (node)
		lst_remove(&table[hash(key) % TABLE_SIZE], node, del_var);
}

void	table_clear(t_list *table[TABLE_SIZE], void (*del)(void*))
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		lst_clear(&table[i], del);
		i++;
	}
}
