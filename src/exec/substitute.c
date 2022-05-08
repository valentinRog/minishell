/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:32:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/08 09:03:13 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	replace_var(t_dy_str *dy_str, char *str, t_shell *shell)
{
	char	*key;
	size_t	i;
	t_list	*node;
	char	*val;
	char	exit_code_str[15];

	i = 0;
	while (str[i] && !str_chr(QUOTES SPACES "$", str[i]))
		i++;
	key = str_n_dup(str, i);
	val = NULL;
	if (!str_cmp(key, "?"))
	{
		itoa(g_exit_code, exit_code_str, 15);
		dy_str_append_str(dy_str, exit_code_str);
	}
	else
	{
		node = table_find(shell->table, key);
		if (node)
			val = ((t_var *)node->content)->data;
		dy_str_append_str(dy_str, val);
	}
	free(key);
	return (i);
}

void	replace_vars(char **dst, t_shell *shell)
{
	size_t		i;
	char		quote;
	t_dy_str	dy_str;

	if (!dst || !*dst)
		return ;
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
	t_list	*new_args;
	t_list	*dir_list;
	t_list	*node;

	dir_list = get_dir_list();
	new_args = get_new_args(cmd->args, shell, dir_list);
	lst_clear(&cmd->args, free);
	cmd->args = new_args;
	replace_vars((char **)&cmd->infile, shell);
	node = cmd->outfiles;
	while (node)
	{
		replace_vars((char **)&node->content, shell);
		node = node->next;
	}
	lst_clear(&dir_list, free);
	return ((bool)(errno == ENOMEM || !new_args));
}
