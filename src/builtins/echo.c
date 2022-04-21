/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:52:21 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/21 10:05:06 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int		i;
	bool	n;

	n = false;
	i = 1;
	if (str_n_cmp(cmd[0], "echo", str_len(cmd[0])) != 0)
		return ;
	if (str_n_cmp(cmd[1], "-n", str_len(cmd[1])) == 0)
	{
		n = true;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
	}
	if (n == false)
		printf("\n");
}
