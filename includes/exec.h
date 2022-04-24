/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:33:26 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/24 20:59:10 by vrogiste         ###   ########.fr       */
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
	t_list	*table[TABLE_SIZE];
}	t_exec;

/*launcher*/
void	launcher(t_list *lst, int z, t_list *table[TABLE_SIZE], t_list **alst);

/*pipex*/
void	pipex(t_list *lst, t_list *table[TABLE_SIZE], t_list **alst);

#endif
