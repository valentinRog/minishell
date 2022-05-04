/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 10:51:18 by bvernimm         ###   ########.fr       */
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

static void	parse_and_launch(char *line, t_shell *shell)
{
	g_exit_code = 0;
	shell->lst = get_parsed_lst(line);
	if (shell->lst)
	{
		launcher(shell->lst, 0, shell);
		lst_clear(&shell->lst, del_cmd);
	}
}

static char	*get_prompt(void)
{
	if (g_exit_code)
		return (C_RED PROMPT C_END);
	return (C_GREEN PROMPT C_END);
}

void	line_is_null(t_shell *shell)
{
	clear_shell(shell);
	if (errno == ENOMEM)
	{
		perror("readline");
		exit(EXIT_FAILURE);
	}
	put_str_fd(" --- exit minishell ---\n", STDIN_FILENO);
	exit(EXIT_SUCCESS);
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
		init_sig();
		line = readline(get_prompt());
		if (!line)
			line_is_null(&shell);
		add_history(line);
		parse_and_launch(line, &shell);
		free(line);
	}
	clear_shell(&shell);
	clear_history();
	return (0);
}
