/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:35:37 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/16 18:20:58 by vrogiste         ###   ########.fr       */
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
	z_index(RESET);
	str_tok(NULL, NULL, NULL);
	if (errno == ENOMEM)
		perror("");
	else
		printf("syntax error near token `%s`\n", token);
}

static t_cmd	*parse_con(t_list **alst, t_cmd *cmd, char *con)
{
	t_cmd	*n_cmd;

	n_cmd = cmd;
	if (get_con(con))
	{
		if (!cmd->args && !cmd->limiters && !cmd->outfiles && !cmd->infile)
		{
			del_cmd(cmd);
			return (NULL);
		}
		cmd->con = get_con(con);
		n_cmd = add_new_cmd(alst);
	}
	return (n_cmd);
}

static void	parse_into_lst(t_list **alst, char *line, t_tok *tok)
{
	t_cmd	*cmd;
	char	*arg;
	char	*con;

	cmd = add_new_cmd(alst);
	while (cmd)
	{
		arg = str_tok(&con, line, tok);
		cmd = parse_con(alst, cmd, con);
		if (!cmd)
			return (parsing_error(alst, arg, con));
		if (!arg)
			break ;
		if (parse_arg(cmd, arg, con))
			return (parsing_error(alst, arg, con));
		free(arg);
	}
	if (z_index(NONE) > 0)
		return (parsing_error(alst, arg, "("));
	if (z_index(NONE) < 0)
		return (parsing_error(alst, arg, ")"));
	str_tok(NULL, NULL, NULL);
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
