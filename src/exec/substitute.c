/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 18:35:36 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab(t_list *lst)
{
	if (lst)
	{
		printf("[");
		while (lst)
		{
			if (lst->prev)
				printf(", ");
			printf("\"%s\"", (char *)lst->content);
			lst = lst->next;
		}
		printf("]\n");
	}
	else
		printf("(null)\n");
}

size_t	replace_var(char **dst, char *str, t_shell *shell)
{
	char	*key;
	size_t	i;
	t_list	*node;
	char	*val;

	str++;
	i = 0;
	key = str_dup1();
	while (str[i] && str[i] != ' ' && str[i] != '\"')
	{
		str_n_insert(&key, str + i, str_len(key), 1);
		i++;
	}
	node = table_find(shell->table, key);
	free(key);
	if (node)
	{
		val = ((t_var *)node->content)->data;
		str_n_insert(dst, val, str_len(*dst), str_len(val));
	}
	while (str[i] && str[i] != ' ' && str[i] != '\"')
		i++;
	return (i);
}

void	split_into_lst(t_list **alst, char *str, t_shell *shell)
{
	size_t	i;
	char	*content;
	char	quote;

	i = 0;
	content = str_dup1();
	quote = '\0';
	while (str[i] && (str[i] != '*' || quote))
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote == str[i])
			quote = '\0';
		else if (str[i] == '$' && quote != '\'')
			i += replace_var(&content, str + i, shell);
		else
			str_n_insert(&content, str + i, str_len(content), 1);
		i++;
	}
	lst_add_back(alst, lst_new(content));
	if (str[i])
		split_into_lst(alst, str + i + 1, shell);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	for (t_list *node = cmd->args; node; node = node->next)
	{
		t_list	*lst = NULL;
		split_into_lst(&lst, node->content, shell);
		print_tab(lst);
	}
	return (false);
}
