/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_index.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:19:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/03 13:47:58 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		z_index(int	op)
{
	static int z_index;

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
	char	*ptr;
	ptr = str;
	while (*ptr)
	{
		skip_white_space(&ptr, WHITESPACES, QUOTES);
		if (*ptr == '(')
		{
			z_index(INCREMENT);
			*ptr = ' ';
		}
		else
			break;
	}
	if (ft_strstr(str, "(", QUOTES))
		return (true);
	cmd->z_index = z_index(NONE);
	ptr = ft_strstr(str, ")", QUOTES);
	while (ptr && *ptr)
	{
		z_index(DECREMENT);
		*ptr = ' ';
		skip_white_space(&ptr, WHITESPACES, QUOTES);
		if (*ptr && *ptr != ')')
			return (true);
	}
	return (false);
}