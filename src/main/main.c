/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/29 23:30:01 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_shell	shell;

	shell.lst = NULL;
	(void) argc;
	(void) argv;
	init_env(shell.table, env);
	while (true)
	{
		line = readline(PROMPT);
		if (!line)
		{
			lst_clear(&shell.lst, del_cmd);
			clear_history();
			exit (EXIT_FAILURE);
		}
		add_history(line);
		shell.lst = get_parsed_lst(line);
		free(line);
		launcher(shell.lst, 0, &shell);
		lst_clear(&shell.lst, del_cmd);
	}
	clear_history();
	return (0);
}
