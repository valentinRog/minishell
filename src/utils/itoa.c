/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:50:43 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 22:10:17 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	number_of_digits(int nb)
{
	int64_t	n;

	n = (int64_t) nb;
	if (n < 0)
		n *= -1;
	if (n < 10)
		return (1);
	return (1 + number_of_digits(n / 10));
}

void	itoa(int nb, char buff[], size_t buffer_size)
{
	size_t	i;
	int64_t	n;

	i = number_of_digits(nb);
	if (buffer_size)
		*buff = '\0';
	n = (int64_t) nb;
	if (i + (n < 0) < buffer_size)
	{
		if (n < 0)
		{
			buff[0] = '-';
			n *= -1;
			i++;
		}
		buff[i--] = '\0';
		while (n)
		{
			buff[i] = n % 10 + '0';
			n /= 10;
			i--;
		}
	}
}
