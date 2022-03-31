/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/03/31 15:30:21 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*lst;

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
		lst = parse(line);
		free(line);
		//execute(lst);
	}
	clear_history();
	return (0);
}
