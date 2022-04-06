/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:42:54 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 13:04:52 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_list	*lst;

	lst = NULL;
	char	str[] = "| |  salut \"||\" a \"&& tous||   a \"&&";
	char	*connectors[4] = {"|", "&&", "||", NULL};
	char	*connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
	connector = str_tok(&line, str, connectors, QUOTES);
	printf("%s\n", line);
	printf("%s\n", connector);
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
