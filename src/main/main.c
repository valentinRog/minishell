/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/03 15:35:41 by bvernimm         ###   ########.fr       */
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
		init_sig();
		line = readline(PROMPT);
		if (!line)
		{
			clear_shell(&shell);
			clear_history();
			signal_handler(4);
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
