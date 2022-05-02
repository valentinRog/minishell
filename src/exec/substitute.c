/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 23:29:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lst_append(t_list **alst, t_list *lst)
{
	t_list	*next;

	if (lst)
	{
		next = lst->next;
		lst_add_back(alst, lst);
		lst_append(alst, next);
	}
}

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

bool	is_ok(t_list *lst, char *str)
{
	return (true);
}

t_list	*get_wild_lst(char *str, t_shell *shell, t_list *dir_list)
{
	t_list	*lst;
	t_list	*wild_lst;

	lst = NULL;
	split_into_lst(&lst, str, shell);
	wild_lst = NULL;
	if (lst_size(lst) == 1)
		return (lst_new(str_dup(lst->content)));
	for (t_list *node = dir_list; node; node = node->next)
	{
		if (is_ok(lst, node->content))
			lst_add_back(&wild_lst, lst_new(str_dup(node->content)));
	}
	return (wild_lst);
}

t_list	*get_dir_list(void)
{
	t_list	*dir_list;
	DIR *d;
	struct dirent *dir;

	dir_list = NULL;
	d = opendir(".");
	while ((dir = readdir(d)))
		lst_add_back(&dir_list, lst_new(str_dup(dir->d_name)));
	closedir(d);
	return (dir_list);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	t_list	*new_args;
	t_list	*dir_list;
	t_list	*node;

	new_args = NULL;
	dir_list = get_dir_list();
	node = cmd->args;
	while (node)
	{
		lst_append(&new_args, get_wild_lst(node->content, shell, dir_list));
		node = node->next;
	}
	lst_clear(&cmd->args, free);
	cmd->args = new_args;
	return (false);
}
