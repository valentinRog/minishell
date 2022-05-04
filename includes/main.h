/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:52:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 12:03:01 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

# define PROMPT "minishell>"

# define C_GREEN "\033[92m"
# define C_RED "\033[91m"
# define C_END "\033[0m"

int	g_exit_code;

typedef struct s_shell
{
	t_list	*table[TABLE_SIZE];
	t_list	*lst;
}	t_shell;

/*clear*/
void	clear_shell(t_shell *shell);

/*signals*/
void	signal_handler(int sig);
void	ctrl_c(int sig);
void	init_sig(void);

/*exit_code*/
char	*exit_code_str(void);

/*main*/
char	*get_prompt(void);

#endif
