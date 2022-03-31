/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 00:38:13 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse(const char *line)
{
	char	*ptr;
	t_list	*lst;
	char	*word;

	lst = NULL;
	ptr = (char *)line;
	while ((word = get_next_word(ptr, " ")))
	{
		printf("%s\n", word);
		skip_next_word(&ptr, " ");
	}
	return (lst);
}
