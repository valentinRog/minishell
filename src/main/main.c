/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 07:28:01 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error(char *msg, t_shell *shell)
{
	if (errno && msg)
		perror(msg);
	else if (msg)
	{
		put_str_fd("Error: ", STDERR_FILENO);
		put_str_fd(msg, STDERR_FILENO);
		put_str_fd("\n", STDERR_FILENO);
	}
	clear_shell(shell);
	clear_history();
	return (1);
}

void	parse_and_launch(char *line, t_shell *shell)
{
	shell->lst = get_parsed_lst(line);
	if (errno == ENOMEM)
		return ((void) perror("parsing"));
	launcher(shell->lst, 0, shell);
	lst_clear(&shell->lst, del_cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_shell	shell;

	shell.lst = NULL;
	init_env(shell.table, env);
	if (errno == ENOMEM)
		return (error("env", &shell));
	if (argc == 3 && !strcmp(argv[1], "-c"))
		parse_and_launch(argv[2], &shell);
	else if (argc > 1)
		return (error("arguments", &shell));
	while (argc == 1)
	{
		line = readline(PROMPT);
		if (!line)
			return (error("readline", &shell));
		add_history(line);
		parse_and_launch(line, &shell);
		free(line);
	}
	clear_shell(&shell);
	clear_history();
	return (0);
}
