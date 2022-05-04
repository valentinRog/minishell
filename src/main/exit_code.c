/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:04:59 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/03 14:06:39 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_code_str(void)
{
	if (g_exit_code == 0)
		return ("0");
	if (g_exit_code == 258)
		return ("258");
	if (g_exit_code == 126)
		return ("126");
	if (g_exit_code == 127)
		return ("127");
	return ("1");
}
