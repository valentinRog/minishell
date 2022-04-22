/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 17:59:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst;
	t_list	*table[TABLE_SIZE];
	t_list	*exec_lst;

	lst = NULL;
	init_env(table, env);
	//table_print(table);
	while (true)
	{
		line = readline(PROMPT);
		if (!line)
		{
			lst_clear(&lst, del_cmd);
			clear_history();
			exit (EXIT_FAILURE);
		}
		add_history(line);
		lst = get_parsed_lst(line);
		if (lst)
		{
			print_lst(lst);
			exec_lst = get_exec_lst(lst);
			lst_clear(&lst, NULL);
			free(line);
			//cool_recursive_function(exec_lst, 0);
			lst_clear(&exec_lst, del_exec);
		}
	}
	clear_history();
	return (0);
}
