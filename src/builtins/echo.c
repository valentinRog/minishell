/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:52:21 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 12:15:47 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_echo(char **cmds)
{
	int		i;
	bool	n;

	n = false;
	i = 1;
	if (str_n_cmp(cmds[0], "echo", str_len(cmds[0])) != 0)
		return (true);
	if (str_n_cmp(cmds[1], "-n", str_len(cmds[1])) == 0)
	{
		n = true;
		i++;
	}
	while (cmds[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", cmds[i]);
		i++;
	}
	if (n == false)
		printf("\n");
	return (false);
}
