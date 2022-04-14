/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:49:33 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/14 07:13:56 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		printf("[");
		while (arr[i])
		{
			if (i)
				printf(", ");
			printf("\"%s\"", arr[i]);
			i++;
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
		print_tab(cmd->exec_args);
		printf("\"infile\" : ");
		if (cmd->infile)
			printf("%s\n", cmd->infile);
		else
			printf("(null)\n");
		printf("\"outfiles\" : ");
		print_tab(cmd->outfiles);
		if (cmd->append)
			printf("\"append\" : true\n");
		else
			printf("\"append\" : false\n");
		printf("\"limiters\" : ");
		print_tab(cmd->limiters);
		printf("\"con\" : ");
		printf("%d\n", cmd->con);
		printf("\n");
		print_lst(lst->next);
	}
}
