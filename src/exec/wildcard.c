/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:46:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/03 11:08:03 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_ok(t_list *lst, char *word)
{
	size_t	i;
	char	*str;

	if (!lst)
	{
		if (!*(word + 1))
			return true;
		return false;
	}
	str = lst->content;
	i = 0;
	while (word[i])
	{
		if (!str_n_cmp(str, word + i, str_len(str)))
		{
			if (is_ok(lst->next, word + i))
				return (true);
		}
		i++;
	}
	return (false);
}

t_list	*get_match_lst(char *str, t_shell *shell, t_list *dir_list)
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
