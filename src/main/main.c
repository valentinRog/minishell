/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:37:27 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/08 09:36:37 by vrogiste         ###   ########.fr       */
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
	rl_clear_history();
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

static char	*get_prompt(char prompt[PROMPT_MAX])
{
	char	*cwd;
	char	*ptr;

	if (g_exit_code)
		str_n_cpy(prompt, C_RED "✖ " C_END, str_len(C_RED "✖ " C_END));
	else
		str_n_cpy(prompt, C_GREEN "➜ " C_END, str_len(C_GREEN "➜ " C_END));
	cwd = getcwd(NULL, 0);
	str_n_cpy(prompt + strlen(prompt), C_CYAN, strlen(C_CYAN));
	ptr = cwd + str_len(cwd) - 1;
	if (ptr)
	{
		while (*(ptr - 1) != '/')
			ptr--;
		if (str_len(ptr) <= PROMPT_MAX - str_len(prompt) - str_len(C_END " "))
			str_n_cpy(prompt + str_len(prompt), ptr, str_len(ptr));
		free(cwd);
	}
	else
		perror("getcwd");
	str_n_cpy(prompt + str_len(prompt), C_END " ", str_len(C_END " "));
	return (prompt);
}

static char	*get_input(void)
{
	char	*input;
	char	prompt[PROMPT_MAX];

	if (isatty(STDIN_FILENO))
		input = readline(get_prompt(prompt));
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
	rl_clear_history();
	clear_shell(&shell);
	return (0);
}
