/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:50:05 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 16:51:37 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell(t_shell *shell)
{
	if (shell)
	{
		table_clear(shell->table, del_var);
		lst_clear(&shell->lst, del_cmd);
	}
}
