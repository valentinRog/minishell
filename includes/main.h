/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:52:29 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/06 10:30:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

# define PROMPT_MAX 50

# define C_GREEN "\e[1;92m"
# define C_RED "\e[1;91m"
# define C_CYAN "\e[1;96m"
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
void	line_is_null(t_shell *shell);
void	init_sig(void);
int		change_term(bool echo_ctl_chr);

#endif
