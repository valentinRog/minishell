/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 18:14:13 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	replace_var(t_dy_str *dy_str, char *str, t_shell *shell)
{
	char	*key;
	size_t	i;
	t_list	*node;
	char	*val;

	i = 0;
	while (str[i] && !str_chr(QUOTES SPACES "$", str[i]))
		i++;
	key = str_n_dup(str, i);
	val = "";
	if (!str_cmp(key, "?"))
		val = exit_code_str();
	node = table_find(shell->table, key);
	free(key);
	if (node)
		val = ((t_var *)node->content)->data;
	dy_str_append_str(dy_str, val);
	return (i);
}

void	replace_vars(char **dst, t_shell *shell)
{
	size_t		i;
	char		quote;
	t_dy_str	dy_str;

	i = 0;
	quote = '\0';
	dy_str = dy_str_new();
	while ((*dst)[i])
	{
		if (!quote && str_chr(QUOTES, (*dst)[i]))
			quote = (*dst)[i];
		else if (quote == (*dst)[i])
			quote = '\0';
		else if ((*dst)[i] == '$' && quote != '\'')
			i += replace_var(&dy_str, (*dst) + i + 1, shell);
		else
			dy_str_append_c(&dy_str, (*dst)[i]);
		i++;
	}
	free(*dst);
	*dst = str_dup(dy_str.str);
	dy_str_destroy(&dy_str);
}

t_list	*get_new_args(t_list *lst, t_shell *shell, t_list *dir_list)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		lst_append_lst(&new_lst, get_match_lst(lst->content, shell, dir_list));
		lst = lst->next;
	}
	return (new_lst);
}

bool	substitute(t_cmd *cmd, t_shell *shell)
{
	t_list	*new_lst;
	t_list	*dir_list;

	dir_list = get_dir_list();
	new_lst = get_new_args(cmd->args, shell, dir_list);
	lst_clear(&cmd->args, free);
	cmd->args = new_lst;
	lst_clear(&dir_list, free);
	return ((bool)(errno == ENOMEM));
}
