/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:51:01 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 11:17:18 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_connector_arr(void)
{
	char	**arr;

	arr = malloc(4 * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = str_n_dup("||", str_len("||"));
	if (!arr[0])
	{
		str_arr_free(arr);
		return (NULL);
	}
	arr[1] = str_n_dup("&&", str_len("&&"));
	if (!arr[0])
	{
		str_arr_free(arr);
		return (NULL);
	}
	arr[2] = str_n_dup("|", str_len("|"));
	if (!arr[0])
	{
		str_arr_free(arr);
		return (NULL);
	}
	arr[3] = NULL;
	return (arr);
}
