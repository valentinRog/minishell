/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:52:18 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/20 18:07:19 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	str_arr_len(char **arr)
{
	if (arr && *arr)
		return (1 + str_arr_len(arr + 1));
	return (0);
}

void	str_arr_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}
