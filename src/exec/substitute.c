/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/03 14:07:20 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error(char *msg, t_list **alst, char *str)
{
	if (msg)
		perror(msg);
	lst_clear(alst, free);
	if (str)
		free(str);
	return (true);
}

size_t	replace_var(char **dst, char *str, t_shell *shell)
{
	char	*key;
	size_t	i;
	t_list	*node;
	char	*val;

	i = 0;
	key = str_dup1();
	while (str[i] && str[i] != ' ' && str[i] != '\"')
	{
		str_n_insert(&key, str + i, str_len(key), 1);
		i++;
	}
	val = "";
	if (!str_cmp(key, "?"))
		val = exit_code_str();
	node = table_find(shell->table, key);
	if (key)
		free(key);
	if (node)
		val = ((t_var *)node->content)->data;
	str_n_insert(dst, val, str_len(*dst), str_len(val));
	while (str[i] && str[i] != ' ' && str[i] != '\"')
		i++;
	return (i);
}

void	split_wildcard(t_list **alst, char *str, t_shell *shell)
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
			i += replace_var(&content, str + i + 1, shell);
		else
			str_n_insert(&content, str + i, str_len(content), 1);
		i++;
	}
	if (errno == ENOMEM)
		return ((void)error("", alst, content));
	if (!lst_add_back(alst, lst_new(content)))
		return ((void)error("", alst, content));
	if (str[i])
		split_wildcard(alst, str + i + 1, shell);
}

t_list	*get_new_args(t_list *lst, t_shell *shell, t_list *dir_list)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		lst_append_lst(&new_lst, get_match_lst(lst->content, shell, dir_list));
		if (errno == ENOMEM)
		{
			error("", &new_lst, NULL);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_lst);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	t_list	*new_lst;
	t_list	*dir_list;

	dir_list = get_dir_list();
	if (!dir_list)
		return (error("", NULL, NULL));
	new_lst = get_new_args(cmd->args, shell, dir_list);
	lst_clear(&cmd->args, free);
	cmd->args = new_lst;
	lst_clear(&dir_list, free);
	return ((bool)(errno == ENOMEM));
}
