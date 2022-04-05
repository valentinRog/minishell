/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_index.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:19:41 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/05 15:49:14 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	z_index(int op)
{
	static int	z_index;

	if (op == INCREMENT)
		z_index++;
	else if (op == DECREMENT)
		z_index--;
	else if (op == RESET)
		z_index = 0;
	return (z_index);
}
