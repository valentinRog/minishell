/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:52:18 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/07 22:49:38 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_arr_add(char ***arr, char *str)
{
	char	**new_arr;
	size_t	i;

	if (!*arr)
	{
		*arr = malloc(sizeof(char *));
		**arr = NULL;
	}
	i = 0;
	while ((*arr)[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	i = 0;
	while ((*arr)[i])
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	free(*arr);
	*arr = new_arr;
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
	if (arr)
		free(arr);
}
