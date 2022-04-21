/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:17:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/21 16:08:05 by bvernimm         ###   ########.fr       */
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

#endif