#include "minishell.h"

void	print_lst(t_list *lst)
{
	t_list *node = lst;

	while (node)
	{
		printf("-----------------------\n");
		t_cmd *cmd = node->content;
		printf("\"exec_args\": ");
		printf("[");
		for (int i = 0; cmd->exec_args[i]; i++)
		{
			if (i)
				printf(", ");
				printf("%s", cmd->exec_args[i]);
		}
		printf("]\n");
		printf("\"infile:\" %s\n", cmd->infile);
		printf("\"outfile:\" %s\n", cmd->outfile);
		printf("\"append:\" %d\n", cmd->append);
		printf("\"limiter:\" %s\n", cmd->limiter);
		printf("\"outfile:\" %d\n", cmd->z_index);
		printf("\"connector:\" %d\n", cmd->connector);
		node = node->next;
		printf("-----------------------\n");
	}
}