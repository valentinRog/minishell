/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:33:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/07 11:30:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

# define NO_USER "USER : variable not found\n"
# define CMD_NOT_FOUND " : command not found\n"

/*launcher*/
void	launcher(t_list *lst, int z, t_shell *shell);

/*pipex*/
void	close_pipe(int fds[2]);
void	pipex(t_list *lst, int i_pipe[2], t_shell *shell);

/*exec_bin*/
void	exec_bin(char **cmds, t_shell *shell);

/*exec_builtin*/
bool	exec_builtin(t_cmd *cmd, t_shell *shell);

/*dup_std*/
bool	dup_stdin(t_cmd *cmd, int i_pipe[2], t_shell *shell);
bool	dup_stdout(t_cmd *cmd, int o_pipe[2]);

/*heredoc*/
bool	heredoc(t_cmd *cmd, t_shell *shell);

/*error*/
bool	b_exec_error(char *str, t_shell *shell, int i_pipe[2], int o_pipe[2]);
void	e_exec_error(char *str, t_shell *shell);

/*substitute*/
bool	substitute(t_cmd *cmd, t_shell *shell);
void	replace_vars(char **dst, t_shell *shell);

/*wildcard*/
t_list	*get_dir_list(void);
t_list	*get_match_lst(char *str, t_shell *shell, t_list *dir_list);

#endif
