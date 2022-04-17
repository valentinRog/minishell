/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:41:15 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/17 15:56:45 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_con	get_con(char *sep)
{
	if (sep)
	{
		if (!strcmp("||", sep))
			return (con_OR);
		if (!strcmp("&&", sep))
			return (con_AND);
		if (!strcmp("|", sep))
			return (con_PIPE);
	}
	return (con_NONE);
}
