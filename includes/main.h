/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:52:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 13:47:33 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

# define PROMPT "minishell>"

int	g_exit_code;

typedef struct s_shell
{
	t_list	*table[TABLE_SIZE];
	t_list	*lst;
}	t_shell;

#endif
