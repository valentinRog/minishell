/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:52:18 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 10:58:14 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_arr_add(char ***arr, char *str)
{
	char	**tmp;
	char	**new_arr;
	size_t	len;

	len = 0;
	tmp = (*arr);
	while (tmp[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (str_arr_free(*arr));
	len = 0;
	while (tmp[len])
	{
		new_arr[len] = tmp[len];
		len++;
	}
	new_arr[len] = str;
	new_arr[len + 1] = NULL;
	free(*arr);
	(*arr) = new_arr;
}

void	str_arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
