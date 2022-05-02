/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:16:28 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/29 23:23:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_to_line(t_var *var)
{
	char	*line;

	line = malloc((str_len(var->key) + str_len(var->data) + 2) * sizeof(char));
	if (line)
	{
		str_n_cpy(line, var->key, str_len(var->key));
		line[str_len(var->key)] = '=';
		str_n_cpy(line + str_len(var->key) + 1, var->data, str_len(var->data));
	}
	return (line);
}

static char	**env_error(char **env)
{
	str_arr_free(env);
	return (NULL);
}

char	**get_full_env(t_list *table[TABLE_SIZE])
{
	char	**env;
	size_t	i;
	t_list	*node;
	size_t	j;

	env = malloc((table_size(table) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		node = table[i];
		while (node)
		{
			env[j] = var_to_line(node->content);
			if (!env[j])
				return (env_error(env));
			j++;
			node = node->next;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}
