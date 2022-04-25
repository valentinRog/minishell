/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:19:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/25 15:51:35 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_pipex(char *str, int i_pipe[2], int o_pipe[2])
{
	perror(str);
	if (i_pipe)
	{
		close(i_pipe[PIPE_WRITE]);
		close(i_pipe[PIPE_READ]);
	}
	if (o_pipe)
	{
		close(o_pipe[PIPE_WRITE]);
		close(o_pipe[PIPE_READ]);
	}
	g_exit_code = 1;
}
