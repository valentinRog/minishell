/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:49:33 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/08 11:30:27 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_tab(char *str, char **tab)
{
	int	i;

	i = 0;
	if (str)
		printf("%s", str);
	if (tab)
	{
		while (tab[i])
		{
			printf("  %s\n", tab[i]);
			i++;
		}
	}
	else
		printf("  Empty array\n");
	return (0);
}

void	print_lst(t_list *lst)
{
	t_cmd	*cmd;

	if (!lst)
		return ;
	printf("\n");
	cmd = lst->content;
	print_tab("Exec_args :\n", cmd->exec_args);
	if (cmd->infile)
		printf("Infile : %s\n", cmd->infile);
	print_tab("Outfiles :\n", cmd->outfiles);
	if (cmd->append == true)
		printf("Append : TRUE\n");
	else if (cmd->append == false)
		printf("Append : FALSE\n");
	print_tab("limiters :\n", cmd->limiters);
	if (cmd->connector)
		printf("Connector : %s\n", cmd->connector);
	printf("Z_index : %d\n", cmd->z_index);
	if (lst->next)
		print_lst(lst->next);
}
