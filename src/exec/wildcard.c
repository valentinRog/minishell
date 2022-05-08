/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:46:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/08 10:24:55 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		lst_add_back(&dir_list, lst_new(d_name));
		dir = readdir(d);
	}
	closedir(d);
	return (dir_list);
}

static bool	match(t_list *lst, char *word)
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

static t_list	*split_wildcard(char *str)
{
	t_list	*lst;
	char	*ptr;

	lst = lst_new(NULL);
	ptr = str;
	while (*ptr && (*ptr != '*' || in_quote(str, ptr, ptr - str)))
		ptr++;
	lst->content = str_n_dup(str, ptr - str);
	if (*ptr == '*')
		lst_append_lst(&lst, split_wildcard(ptr + 1));
	return (lst);
}

t_list	*get_match_lst(char *str, t_shell *shell, t_list *dir_list)
{
	t_list	*lst;
	t_list	*match_lst;
	t_list	*node;

	lst = split_wildcard(str);
	node = lst;
	while (node)
	{
		replace_vars((char **)&node->content, shell);
		node = node->next;
	}
	match_lst = NULL;
	if (lst_size(lst) == 1)
		lst_add_back(&match_lst, new_lst_str(lst->content));
	else
	{
		while (dir_list)
		{
			if (match(lst, dir_list->content))
				lst_add_back(&match_lst, new_lst_str(dir_list->content));
			dir_list = dir_list->next;
		}
	}
	lst_clear(&lst, free);
	return (match_lst);
}
