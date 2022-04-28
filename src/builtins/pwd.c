/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:23:51 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/28 10:31:55 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bi_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (errno == ENOMEM)
		return (true);
	printf("%s\n", path);
	free (path);
	return (false);
}
