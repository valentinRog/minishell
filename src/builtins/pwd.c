/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:23:51 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/26 14:51:06 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (errno == ENOMEM)
		return ;
	printf("%s\n", path);
	free (path);
}
