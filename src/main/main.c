/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 02:21:55 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	while (true)
	{
		line = readline(PROMPT);
		if (!line)
		{
			perror("");
			clear_history();
			exit (EXIT_FAILURE);
		}
		add_history(line);
		parse(&lst, line);
		free(line);
		//execute(lst);
	}
	clear_history();
	return (0);
}
