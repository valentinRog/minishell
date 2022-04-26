/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:52:21 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/26 14:50:04 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_echo(char **cmd)
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
