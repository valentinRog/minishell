/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 16:11:56 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cool_recursive_function(t_list *lst, int z_index)
{
	int	ret;

	while(lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
	{
		if (((t_exec *)lst->content)->cmd->con == con_PIPE)
		{
			//pipex
			lst = lst->next;
			continue ;
		}
		if (((t_exec *)lst->content)->cmd->z_index > z_index)
		{
			ret = cool_recursive_function(lst, z_index + 1);
			while(lst && ((t_exec *)lst->content)->cmd->z_index > z_index)
				lst = lst->next;
		}
		else
		{
			printf("%s\n", ((t_exec *)lst->content)->cmd->args->content);
			if (*((char *)(((t_exec *)lst->content)->cmd->args->content)) == '0')
				ret = 0;
			else
				ret = 1;
		}
		if (ret == 0 && ((t_exec *)lst->content)->cmd->con == con_AND)
			break ;
		else if (ret == 1 && ((t_exec *)lst->content)->cmd->con == con_OR)
			break ;
		lst = lst->next;
	}
	printf("%p\n", lst);
	return (ret);
}
