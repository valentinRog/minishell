/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 14:03:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	t_list	*table[TABLE_SIZE];
	init_env(table, env);
	table_print(table);
	table_remove(table, "HOME");
	table_remove(table, "HOME");
	table_print(table);
	/*
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
		free(line);
		print_lst(lst);
		lst_clear(&lst, del_cmd);
	}
	clear_history();*/
	return (0);
}
