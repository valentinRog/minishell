/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/02 15:49:17 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tab(t_list *lst)
{
	if (lst)
	{
		printf("[");
		while (lst)
		{
			if (lst->prev)
				printf(", ");
			printf("\"%s\"", (char *)lst->content);
			lst = lst->next;
		}
		printf("]\n");
	}
	else
		printf("(null)\n");
}

void	split_into_lst(t_list **alst, char *str, t_shell *shell)
{
	t_list	*lst;
	size_t	i;
	char	*content;
	lst = NULL;
	i = 0;
	content = str_dup1();
	while (str[i] && (str[i] != '*' || in_quote(str, QUOTES, i)))
	{
		str_n_insert(&content, str + i, str_len(content), 1);
		i++;
	}
	lst_add_back(alst, lst_new(content));
	if (str[i])
		split_into_lst(alst, str + i + 1, shell);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	for (t_list *node = cmd->args; node; node = node->next)
	{
		t_list	*lst = NULL;
		split_into_lst(&lst, node->content, shell);
		print_tab(lst);
	}
	return (false);
}
