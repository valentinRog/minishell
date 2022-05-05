/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:57:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/05 10:45:13 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c(int sig)
{
	(void) sig;
}

void	line_is_null(t_shell *shell)
{
	clear_shell(shell);
	change_term(true);
	if (errno == ENOMEM)
	{
		perror("readline");
		exit(EXIT_FAILURE);
	}
	put_str_fd(" --- exit minishell ---\n", STDIN_FILENO);
	exit(EXIT_SUCCESS);
}

void	init_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	change_term(false);
}

int	change_term(bool echo_ctl_chr)
{
	struct termios	term;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &term);
	if (status == -1)
		return (1);
	if (echo_ctl_chr)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	if (status == -1)
		return (1);
	return (0);
}
