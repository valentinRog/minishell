/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 12:17:00 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_str(char *str, t_shell *shell)
{
	char	*dst;
	char	*key;
	size_t	i = 0;
	char	quote = 0;
	dst = str_dup1();
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			i++;
			continue;
		}
		else if (str[i] == '$' && quote != '\'')
		{
			i++;
			key = str_dup1();
			while (str[i] != '\'' && str[i] != '\"' && str[i] && str[i] != '$' && str[i] != ' ')
			{
				str_n_insert(&key, str + i, str_len(key), 1);
				i++;
			}
			char	*val;
			if (table_find(shell->table, key))
				val = ((t_var *)table_find(shell->table, key)->content)->data;
			else
				val = "";
			str_n_insert(&dst, val, str_len(dst), str_len(val));
			continue;
		}
		str_n_insert(&dst, str + i, str_len(dst), 1);
		i++;
	}	
	return (dst);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	for (t_list *node = cmd->args; node; node = node->next)
	{
		node->content = get_new_str(node->content, shell);
	}
	return (false);
}
