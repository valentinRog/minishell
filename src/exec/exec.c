/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 15:20:17 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cool_recursive_function(t_list *lst, int z_index)
{
	int	ret;

	printf("entering %d level of parenthesis\n", z_index);
	while(lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
	{
		if (((t_exec *)lst->content)->cmd->con == con_PIPE)
		{
			lst = lst->next;
			continue ;
		}
		if (((t_exec *)lst->content)->cmd->z_index > z_index)
			ret = cool_recursive_function(lst, z_index + 1);
		else
		{
			printf("%s\n", ((t_exec *)lst->content)->cmd->args->content);
			ret = 1;//insert exec fonction here :)
		}
		if (ret == 0 && ((t_exec *)lst->content)->cmd->con == con_AND)
		{
			while(lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
				lst = lst->next;
			return (0);
		}
		else if (ret == 1 && ((t_exec *)lst->content)->cmd->con == con_OR)
		{
			while(lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
			{
				//printf("%d\n", ((t_exec *)lst->content)->cmd->z_index);
				lst = lst->next;
			}
			return (1);
		}
		lst = lst->next;
	}
	return (ret);
}
