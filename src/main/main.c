/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:37:27 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/05 17:17:40 by vrogiste         ###   ########.fr       */
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

static char	*get_input(void)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline(get_prompt());
	else
		input = get_next_line(STDIN_FILENO);
	return (input);
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
		line = get_input();
		if (!line)
			line_is_null(&shell);
		add_history(line);
		parse_and_launch(line, &shell);
		free(line);
	}
	clear_history();
	clear_shell(&shell);
	return (0);
}
