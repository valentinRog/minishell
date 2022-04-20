/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:08:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 14:24:33 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint64_t	hash(char *key)
{
	uint64_t	sum;

	sum = 0;
	while (key && *key)
	{
		sum += *key;
		key++;
	}
	return (sum);
}

t_list	*table_find(t_list *table[TABLE_SIZE], char *key)
{
	t_list	*lst;

	lst = table[hash(key) % TABLE_SIZE];
	while (lst)
	{
		if (!str_cmp(((t_var *)lst->content)->key, key))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	table_init(t_list *table[TABLE_SIZE])
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		table[i] = NULL;
		i++;
	}
}

size_t	table_size(t_list *table[TABLE_SIZE])
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (i < TABLE_SIZE)
	{
		size += lst_size(table[i]);
		i++;
	}
	return (size);
}

void	table_print(t_list *table[TABLE_SIZE])
{
	size_t	i;
	t_list	*node;

	i = 0;
	printf("--------------------\n");
	while (i < TABLE_SIZE)
	{
		printf("#%zu", i);
		node = table[i];
		while (node)
		{
			printf("->%s", ((t_var *)node->content)->key);
			node = node->next;
		}
		printf("\n");
		i++;
	}
	printf("--------------------\n");
}
