/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/27 10:12:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*add_new_cmd(t_list **alst)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	new_node = lst_new(cmd);
	if (!new_node)
	{
		del_cmd(cmd);
		return (NULL);
	}
	lst_add_back(alst, new_node);
	return (cmd);
}

static void	parsing_error(t_list **alst, char *arg, char *token)
{
	lst_clear(alst, del_cmd);
	if (arg)
		free(arg);
	z_index(z_RESET);
	str_tok(NULL, NULL, NULL);
	if (errno == ENOMEM)
		perror("");
	else if (token)
	{
		printf("syntax error near token `%s`\n", token);
		g_exit_code = 258;
	}
}

static void	check_parsed_lst(t_list **alst)
{
	t_list	*node;
	t_cmd	*cmd;

	node = *alst;
	while (node)
	{
		cmd = node->content;
		if (!cmd->args && !cmd->infile && !cmd->outfiles && !cmd->heredoc)
		{
			if (node->prev && ((t_cmd *)node->prev->content)->con == con_PIPE)
				return (parsing_error(alst, NULL, "|"));
			if (node->prev && ((t_cmd *)node->prev->content)->con == con_AND)
				return (parsing_error(alst, NULL, "&&"));
			if (node->prev && ((t_cmd *)node->prev->content)->con == con_OR)
				return (parsing_error(alst, NULL, "||"));
			return (parsing_error(alst, NULL, NULL));
		}
		node = node->next;
	}
	if (z_index(z_NONE) > 0)
		return (parsing_error(alst, NULL, "("));
	if (z_index(z_NONE) < 0)
		return (parsing_error(alst, NULL, ")"));
	str_tok(NULL, NULL, NULL);
}

static void	parse_into_lst(t_list **alst, char *line, t_tok *tok)
{
	t_cmd	*cmd;
	char	*arg;
	char	*con;

	if (!*alst)
		add_new_cmd(alst);
	cmd = (t_cmd *)((lst_last(*alst))->content);
	arg = str_tok(&con, line, tok);
	if (arg)
	{
		if (get_con(con))
		{
			cmd->con = get_con(con);
			cmd = add_new_cmd(alst);
			if (!cmd)
				return (parsing_error(alst, arg, NULL));
		}
		if (parse_arg(cmd, arg, con))
			return (parsing_error(alst, arg, con));
		free(arg);
		return (parse_into_lst(alst, line, tok));
	}
	check_parsed_lst(alst);
}

t_list	*get_parsed_lst(char *line)
{
	t_list	*lst;
	t_tok	tok;

	lst = NULL;
	tok.seps = split(">>:<<:<:>:&&:||:|:(:)", ':');
	if (!tok.seps)
		return (NULL);
	tok.quotes = QUOTES;
	tok.spaces = SPACES;
	parse_into_lst(&lst, line, &tok);
	str_arr_free(tok.seps);
	return (lst);
}
