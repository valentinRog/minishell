/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:33:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/22 18:16:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef struct s_exec
{
	t_cmd	*cmd;
	int		fds[2];
	int		fd_in;
	int		fd_out;
	int		pid;
	int		exit_code;
}	t_exec;

/*init_exec_lst*/
void	del_exec(t_exec *exec);
t_list	*get_exec_lst(t_list *parsed_lst);

/*exec*/
int		cool_recursive_function(t_list *lst, int z_index);

#endif