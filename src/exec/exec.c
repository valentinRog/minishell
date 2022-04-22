/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 05:12:36 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 18:30:35 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cool_recursive_function(t_list *lst, int z_index)
{
	int	ret;

	ret = 0;
	while(lst && ((t_exec *)lst->content)->cmd->z_index >= z_index)
	{
		// if (((t_exec *)lst->content)->cmd->con == con_PIPE)
		// {
		// 	//pipex
		// 	lst = lst->next;
		// 	continue ;
		// }
		if (((t_exec *)lst->content)->cmd->z_index > z_index)
		{
			ret = cool_recursive_function(lst, ((t_exec *)lst->content)->cmd->z_index);
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
		if (!lst)
			return ret;
		if (ret == 0 && ((t_exec *)lst->content)->cmd->con == con_AND)
			break ;
		else if (ret == 1 && ((t_exec *)lst->content)->cmd->con == con_OR)
			break ;
		lst = lst->next;
	}
	return (ret);
}
