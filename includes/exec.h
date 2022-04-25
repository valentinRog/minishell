/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:33:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/25 16:00:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

# define BUILTINS "echo:cd:pwd:export:unset:env:exit"

/*launcher*/
void	launcher(t_list *lst, int z, t_list **alst);

/*pipex*/
void	pipex(t_list *lst, t_list **alst, int fds[2]);

/*error_pipex*/
void	error_pipex(char *str, int i_pipe[2], int o_pipe[2]);

/*exec_builtins*/
void	exec_builtin(t_cmd *cmd, int o_pipe[2]);

#endif
