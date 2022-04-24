/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 21:11:46 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/24 21:11:48 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_env(t_list *table[TABLE_SIZE]);
void	ft_echo(char **cmd);
void	ft_pwd(void);
void	ft_cd(char **cmd);
void	ft_export(char **cmd, t_list *table[TABLE_SIZE]);
void	ft_unset(char **cmd, t_list *table[TABLE_SIZE]);

#endif
