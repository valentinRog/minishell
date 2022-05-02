/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 18:07:55 by vrogiste         ###   ########.fr       */
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

char	*get_value(char *str, t_shell *shell)
{
	char	*key = str_dup1();

	size_t	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"')
	{
		str_n_insert(&key, str + i, str_len(key), 1);
		i++;
	}
	t_list	*node = table_find(shell->table, key);
	free(key);
	if (node)
		return ((t_var *)node->content)->data;
	return ("");
}

size_t	yo(char **dst, char *str, t_shell *shell)
{
	size_t	i;

	i = 1;
	str_n_insert(dst, get_value(str + 1, shell), str_len(*dst), str_len(get_value(str + 1, shell)));
	while (str[i] && str[i] != ' ' && str[i] != '\"')
				i++;
	return (i - 1);
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
			i += yo(&content, str + i, shell);
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
