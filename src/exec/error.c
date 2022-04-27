/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:41:28 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 17:00:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_error(char *str, t_shell *shell, int i_pipe[2], int o_pipe[2])
{
	if (str)
		perror(str);
	clear_shell(shell);
	close_pipe(i_pipe);
	close_pipe(o_pipe);
	g_exit_code = 1;
	return (true);
}
