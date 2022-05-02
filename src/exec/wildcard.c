/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 23:46:25 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 23:47:01 by vrogiste         ###   ########.fr       */
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
