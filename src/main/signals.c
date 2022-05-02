/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:57:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/02 14:13:18 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dtrap(void)
{
	write(2, "\b\bexit\n", 7);
	exit (0);
}

void	ctrap(int sig)
{
	static bool	prev;

	if (sig == 2)
	{
		if (prev == true)
			write(2, "\b\b  ", 4);
		write(2, "\n", 1);
		write(2, PROMPT, str_len(PROMPT));
		prev = true;
	}
	else
		prev = false;
}

void	slashtrap(int sig)
{
	static bool	prev;

	if (sig == 3)
	{
		if (prev == true)
			write(2, "\b\b  \b\b", 6);
		prev = true;
	}
	else
		prev = false;
}

void	init_sig(void)
{
	(void) signal(SIGINT, ctrap);
	(void) signal(SIGQUIT, slashtrap);
	ctrap(0);
	slashtrap(0);
}
