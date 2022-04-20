/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:11:57 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 10:15:15 by vrogiste         ###   ########.fr       */
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
