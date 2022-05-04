/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:46:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 07:24:35 by vrogiste         ###   ########.fr       */
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
		if (!str_n_cmp(lst->content, word + i, str_len(lst->content)))
			if (match(lst->next, word + i))
				return (true);
		if (!lst->prev)
			break ;
		i++;
	}
	return (false);
}

t_list	*get_match_lst(char *str, t_shell *shell, t_list *dir_list)
{
	t_list	*lst;
	t_list	*wild_lst;

	lst = NULL;
	split_wildcard(&lst, str, shell);
	if (!lst)
		return (error("", NULL, NULL));
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
	if (errno == ENOMEM)
		return (error("", &wild_lst, NULL));
	return (wild_lst);
}
