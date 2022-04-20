/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:08:14 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 07:18:19 by vrogiste         ###   ########.fr       */
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

bool	add_var(t_list *table[TABLE_SIZE], t_table_var *var)
{
	lst_add_back(&table[hash(var->key) % TABLE_SIZE], lst_new(var));
	return false;
}

void	init_table(t_list *table[TABLE_SIZE])
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		table[i] = NULL;
		i++;
	}
}

void	print_table(t_list *table[TABLE_SIZE])
{
	printf("--------------------\n");
	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		printf("#%zu", i);
		for (t_list *node = table[i]; node; node = node->next)
			printf("->%s", ((t_table_var *)node->content)->key);
		printf("\n");
	}
	printf("--------------------\n");
}