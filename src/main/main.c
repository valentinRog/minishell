/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 17:50:22 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	char	*str = strdup("bonjour");
	str_n_insert(&str, "salut", 3, 2);
	printf("%s\n", str);
	printf("%"PRId64"\n", min(40, 5));
	/*while (true)
	{
		line = readline(PROMPT);
		if (!line)
		{
			lst_clear(&lst, del_cmd);
			clear_history();
			exit (EXIT_FAILURE);
		}
		add_history(line);
		lst = get_parsed_lst(line);
		if (!lst)
		{
			lst_clear(&lst, del_cmd);
			//clear_history();
			//exit (EXIT_FAILURE);
			printf("parsing error\n");
		}
		else
		{
			print_lst(lst);
			free(line);
			lst_clear(&lst, del_cmd);
		}
		//execute(lst);
	}
	clear_history();*/
	return (0);
}
