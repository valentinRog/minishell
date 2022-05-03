/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:57:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/03 15:39:04 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	signal_handler(int sig)
{
	static bool	prev;

	if (sig == SIGINT)
	{
		if (prev == true)
			write(1, "\b\b  ", 4);
		write(1, "\n", 1);
		write(1, PROMPT, str_len(PROMPT));
		prev = true;
	}
	else if (sig == SIGQUIT)
	{
		if (prev == true)
			write(1, "\b\b  \b\b", 6);
		prev = true;
	}
	else if (sig == 4)
	{
		if (prev == false)
			write(1, "\b\b", 2);
		write(1, "exit\n", 5);
		exit (0);
	}
	else if (sig == 0)
		prev = false;
}*/

/*int		globallol(int code)
{
	static int	not_a_global;

	if (code != 0)
		not_a_global = code;
	printf("\ncode : %d, global : %d\n", code, not_a_global);
	return (not_a_global);
}*/

void	signal_handler(int sig)
{
	static bool	prev;

	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		prev = true;
	}
	else if (sig == SIGQUIT)
	{
		if (prev == true)
			write(1, "\b\b  \b\b", 6);
		prev = true;
	}
	else if (sig == 4)
	{
		if (prev == false)
			write(2, "\b\b", 2);
		write(2, "exit\n", 5);
		exit (0);
	}
	else if (sig == 0)
		prev = false;
}

void	init_sig(void)
{
	(void) signal(SIGINT, signal_handler);
	(void) signal(SIGQUIT, signal_handler);
	signal_handler(0);
}
