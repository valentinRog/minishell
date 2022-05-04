/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:46:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 22:59:17 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*error(char *msg, t_list **alst, char *str)
{
	if (msg)
		perror(msg);
	lst_clear(alst, free);
	if (str)
		free(str);
	return (NULL);
}

t_list	*get_dir_list(void)
{
	t_list			*dir_list;
	DIR				*d;
	struct dirent	*dir;
	char			*d_name;

	dir_list = NULL;
	d = opendir(".");
	dir = readdir(d);
	while (dir)
	{
		d_name = str_dup(dir->d_name);
		if (!d_name)
			return (error("", &dir_list, NULL));
		if (!lst_add_back(&dir_list, lst_new(d_name)))
			return (error("", &dir_list, d_name));
		dir = readdir(d);
	}
	closedir(d);
	return (dir_list);
}

bool	match(t_list *lst, char *word)
{
	size_t	i;

	if (!lst)
		return (true);
	i = 0;
	while (word[i])
	{
		if (!lst->next && *(char *)lst->content)
		{
			if (!str_cmp(lst->content, word + i) && match(lst->next, word + i))
				return (true);
		}
		else if (!str_n_cmp(lst->content, word + i, str_len(lst->content)))
			if (match(lst->next, word + i))
				return (true);
		if (!lst->prev)
			break ;
		i++;
	}
	return (false);
}

t_list	*better_split(char *str)
{
	t_list	*lst;
	char	*ptr;
	char	*content;

	lst = NULL;
	ptr = str;
	while (*ptr && (*ptr != '*' || in_quote(str, QUOTES, ptr - str)))
		ptr++;
	content = str_n_dup(str, ptr - str);
	lst = lst_new(content);
	if (*ptr)
		lst_add_back(&lst, better_split(ptr + 1));
	return (lst);
}

/*size_t	replace_var(char **dst, char *str, t_shell *shell)
{
	char	*key;
	size_t	i;
	t_list	*node;
	char	*val;

	i = 0;
	key = str_dup1();
	while (str[i] && !str_chr("\'\" \t", str[i]))
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
	while (str[i] && !str_chr("\'\" \t", str[i]))
		i++;
	return (i);
}

void	replace_all(char **dst, t_shell *shell)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while ((*dst)[i])
	{
		if (!quote && ((*dst)[i] == '\"' || (*dst)[i] == '\''))
		{
			quote = (*dst)[i];
			str_n_remove(dst, i, 1);
		}
		else if (quote == (*dst)[i])
		{
			quote = '\0';
			str_n_remove(dst, i, 1);
		}
		else if ((*dst)[i] == '$' && quote != '\'')
			i += replace_var(&content, (*dst) + i + 1, shell);
		else
			str_n_insert(&content, (*dst) + i, str_len(content), 1);
		i++;
	}
	*dst = content;
}*/

t_list	*get_match_lst(char *str, t_shell *shell, t_list *dir_list)
{
	t_list	*lst;
	t_list	*wild_lst;

	lst = better_split(str);
	/*for (t_list *node = lst; node; node = node->next)
		replace_all(&node->content, shell);
	for (t_list *node = lst; node; node = node->next)
		printf("%s\n", node->content);*/
	wild_lst = NULL;
	if (lst_size(lst) == 1)
		lst_add_back(&wild_lst, new_lst_str(lst->content));
	else
	{
		while (dir_list)
		{
			if (match(lst, dir_list->content))
				lst_add_back(&wild_lst, new_lst_str(dir_list->content));
			dir_list = dir_list->next;
		}
	}
	lst_clear(&lst, free);
	return (wild_lst);
}
