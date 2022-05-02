/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:41:28 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/28 14:32:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	b_exec_error(char *str, t_shell *shell, int i_pipe[2], int o_pipe[2])
{
	if (str)
		perror(str);
	clear_shell(shell);
	close_pipe(i_pipe);
	close_pipe(o_pipe);
	g_exit_code = 1;
	return (true);
}

void	e_exec_error(char *str, t_shell *shell)
{
	if (str)
		perror(str);
	clear_shell(shell);
	exit(EXIT_FAILURE);
}
