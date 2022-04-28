/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 21:11:46 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 14:51:50 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/*echo*/
bool	bi_echo(char **cmds);

/*cd*/
bool	bi_cd(char **cmds);

/*pwd*/
bool	bi_pwd(void);

/*export*/
bool	bi_export(char **cmds, t_shell *shell);

/*unset*/
bool	bi_unset(char **cmds, t_shell *shell);

/*env*/
bool	bi_env(t_shell *shell);

/*exit*/
void	bi_exit(t_shell *shell);

#endif
