/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:11 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 14:29:19 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dy_str	dy_str_new(void)
{
	t_dy_str	dy_str;

	dy_str.alloc = 0;
	dy_str.str = str_dup1();
	if (dy_str.str)
		dy_str.alloc = 1;
	return (dy_str);
}

void	dy_str_destroy(t_dy_str *dy_str)
{
	if (dy_str->alloc)
	{
		free(dy_str->str);
		dy_str->alloc = 0;
	}
}

void	dy_str_grow(t_dy_str *dy_str)
{
	char	*new_str;

	dy_str->alloc *= 2;
	new_str = malloc(dy_str->alloc * sizeof(char));
	str_n_cpy(new_str, dy_str->str, str_len(dy_str->str));
	free(dy_str->str);
	dy_str->str = new_str;
}

void	dy_str_append_c(t_dy_str *dy_str, char c)
{
	if (str_len(dy_str->str) == dy_str->alloc - 1)
		dy_str_grow(dy_str);
	dy_str->str[str_len(dy_str->str) + 1] = '\0';
	dy_str->str[str_len(dy_str->str)] = c;
}
