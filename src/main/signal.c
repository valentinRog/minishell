/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:57:56 by bvernimm          #+#    #+#             */
/*   Updated: 2022/05/05 09:45:35 by bvernimm         ###   ########.fr       */
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

void	init_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	termios_change(false);
}

int	termios_change(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	if (echo_ctl_chr)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
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
