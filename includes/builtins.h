/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 21:11:46 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 14:51:50 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/*echo*/
void	bi_echo(char **cmd);

/*cd*/
void	bi_cd(char **cmd);

/*pwd*/
void	bi_pwd(void);

/*export*/
void	bi_export(char **cmd, t_list *table[TABLE_SIZE]);

/*unset*/
void	bi_unset(char **cmd, t_list *table[TABLE_SIZE]);

/*env*/
void	bi_env(t_list *table[TABLE_SIZE]);

/*exit*/
void	bi_exit(void);

#endif
