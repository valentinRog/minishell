/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:48:06 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/30 17:57:29 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_loop(void)
{
	char	*line;

	while (true)
	{
		line = readline(PROMPT);
		printf("%s\n", line);
		free(line);
	}
}
