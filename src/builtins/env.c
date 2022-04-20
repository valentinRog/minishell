/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:17:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 19:45:25 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmp(void *arg_1, void *arg_2)
{
	t_var	*var_1;
	t_var	*var_2;

	var_1 = (t_var *) arg_1;
	var_2 = (t_var *) arg_2;
	return (str_cmp_no_case(var_1->key, var_2->key));	
}

void	ft_env(t_list *table[TABLE_SIZE])
{
	t_list	*lst;
	size_t	i;
	t_list	*node;
	t_var	*var;

	i = 0;
	lst = NULL;
	while (i < TABLE_SIZE)
	{
		node = table[i];
		while (node)
		{
			lst_add_back(&lst, lst_new(node->content));
			node = node->next;
		}
		i++;
	}
	node = lst;
	lst_sort(lst, env_cmp);
	while (node)
	{
		var = (t_var *) node->content;
		printf("%s=%s\n", var->key, (char *)var->data);
		node = node->next;
	}
	lst_clear(&lst, del_var);
}
