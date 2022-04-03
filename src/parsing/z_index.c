/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_index.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:19:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/03 13:53:14 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	z_index(int op)
{
	static int	z_index;

	if (op == INCREMENT)
		z_index++;
	else if (op == DECREMENT)
		z_index--;
	else if (op == RESET)
		z_index = 0;
	return (z_index);
}

bool	get_z_index(t_cmd *cmd, char *str)
{
	skip_white_space(&str, WHITESPACES, QUOTES);
	while (*str == '(')
	{
		skip_white_space(&str, WHITESPACES, QUOTES);
		if (*str == '(')
		{
			z_index(INCREMENT);
			*str = ' ';
		}
	}
	if (ft_strstr(str, "(", QUOTES))
		return (true);
	cmd->z_index = z_index(NONE);
	str = ft_strstr(str, ")", QUOTES);
	while (str && *str)
	{
		z_index(DECREMENT);
		*str = ' ';
		skip_white_space(&str, WHITESPACES, QUOTES);
		if (*str && *str != ')')
			return (true);
	}
	return (false);
}
