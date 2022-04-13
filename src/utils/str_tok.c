/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:59:23 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 15:11:48 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_con(char *str, size_t i, t_tok *tok)
{
	char	**seps;

	seps = tok->seps;
	while (seps && *seps)
	{
		if (!in_quote(str, tok->quotes, i))
		{
			if (!str_n_cmp(str + i, *seps, str_len(*seps)))
				return (*seps);
		}
		seps++;
	}
	return (NULL);
}

char	*str_tok(char **astr, char *src, t_tok *tok)
{
	static char	*ptr;
	char		*start;

	if (!src || !ptr || !tok)
		ptr = src;
	if (!tok || !src)
		return (NULL);
	while (in_str(tok->spaces, *ptr) && !in_quote(src, tok->quotes, ptr - src))
		ptr++;
	if (!*ptr)
		return (NULL);
	if (astr)
		*astr = get_con(src, ptr - src, tok);
	ptr += str_len(get_con(src, ptr - src, tok));
	while (in_str(tok->spaces, *ptr) && !in_quote(src, tok->quotes, ptr - src))
		ptr++;
	start = ptr;
	while
	(
		*ptr && !get_con(src, ptr - src, tok)
		&& (!in_str(SPACES, *ptr) || in_quote(src, tok->quotes, ptr - src))
	)
			ptr++;
	return (str_n_dup(start, ptr - start));
}
