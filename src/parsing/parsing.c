/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 10:44:35 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_into_lst(t_list **alst, const char *line)
{
	char	*connector;
	char	*cmd_line;
	t_list	*node;

	connector = str_tok(&cmd_line, line, , QUOTES);
	
}
