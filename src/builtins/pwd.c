/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:23:51 by bvernimm          #+#    #+#             */
/*   Updated: 2022/04/21 10:30:59 by bvernimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (errno == ENOMEM)
		return ;
	printf("%s\n", path);
	free (path);
}