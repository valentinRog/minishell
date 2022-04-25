/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:43:57 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/25 10:18:54 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*init*/
void	del_var(void *arg);
t_var	*str_to_var(char *str);
void	init_env(t_list *table[TABLE_SIZE], char **env);
t_list	**get_table(t_list **new_table);

/*get_full_env*/
char	**get_full_env(t_list *table[TABLE_SIZE]);

#endif