/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:43:57 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/20 14:04:30 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/*init*/
void	del_var(void *arg);
t_var	*str_to_var(char *str);
void	init_env(t_list *table[TABLE_SIZE], char **env);

#endif