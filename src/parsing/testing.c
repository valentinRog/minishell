/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:18:49 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 10:47:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	printf("\n########################################\n");
	for (size_t i = 1; lst; i++)
	{
		printf("----------%zu----------\n", i);
		t_cmd *cmd = lst->content;
		printf("\"exec_args\": ");
		printf("[");
		if (!cmd->exec_args)
			printf("%p", NULL);
		else
		{
			for (int j = 0; cmd->exec_args[j]; j++)
			{
				if (j)
					printf(", ");
				printf("%s", cmd->exec_args[j]);
			}
		}
		printf("]\n");
		printf("\"infile\": %s\n", cmd->infile);
		printf("\"outfile\": %s\n", cmd->outfile);
		printf("\"append\": %d\n", cmd->append);
		printf("\"limiter\": %s\n", cmd->limiter);
		printf("\"z_index\": %d\n", cmd->z_index);
		printf("\"connector\": %d\n", cmd->connector);
		lst = lst->next;
		printf("--------------------\n");
	}
}