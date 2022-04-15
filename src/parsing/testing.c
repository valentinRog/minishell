/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:49:33 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/15 09:47:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab(t_list *lst)
{
	if (lst)
	{
		printf("[");
		while (lst)
		{
			if (lst->prev)
				printf(", ");
			printf("\"%s\"", (char *)lst->content);
			lst = lst->next;
		}
		printf("]\n");
	}
	else
		printf("(null)\n");
}

void	print_lst(t_list *lst)
{
	t_cmd	*cmd;

	if (lst)
	{
		cmd = (t_cmd *)lst->content;
		if (!lst->prev)
			printf("---------------------------------\n");
		printf("\"exec_args\" : ");
		print_tab(cmd->args);
		printf("\"infile\" : ");
		if (cmd->infile)
			printf("\"%s\"\n", cmd->infile);
		else
			printf("(null)\n");
		printf("\"outfiles\" : ");
		print_tab(cmd->outfiles);
		printf("\"append\" : %d\n", cmd->append);
		printf("\"limiters\" : ");
		print_tab(cmd->limiters);
		printf("\"con\" : %d\n", cmd->con);
		printf("\"z_index\" : %d\n\n", cmd->z_index);
		print_lst(lst->next);
	}
}
