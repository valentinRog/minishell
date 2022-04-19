/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:46:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/19 18:37:47 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->val)
			free(var->val);
		free(var);
	}
}

t_var	*get_var(char *str)
{
	t_var	*var;
	char	*ptr;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	ptr = ft_memchr(str, '=', strlen(str));
	var->key = str_n_dup(str, ptr - str);
	var->val = str_dup(ptr + 1);
	if (!var->key || !var->val)
	{
		del_var(var);
		return (NULL);
	}
	return (var);
}

t_list	*init_env(char **env)
{
	t_list	*lst;
	t_var	*var;

	lst = NULL;
	while (*env)
	{
		var = get_var(*env);
		lst_add_back(&lst, lst_new(var));
		if (errno == ENOMEM)
		{
			del_var(var);
			lst_clear(&lst, del_var);
			return (NULL);
		}
		env++;
	}
	return (lst);
}
