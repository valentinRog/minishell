/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:41:15 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 19:45:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_con(char *sep)
{
	if (sep)
	{
		if (!strcmp("||", sep))
			return (OR);
		if (!strcmp("&&", sep))
			return (AND);
		if (!strcmp("|", sep))
			return (PIPE);
	}
	return (NONE);
}
