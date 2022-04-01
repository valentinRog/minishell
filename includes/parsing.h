/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/01 04:29:06 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

enum
{
	PIPE,
	AND,
	OR,
	END,
};

# define CONNECTORS "|&"
# define WHITESPACE " "

typedef struct s_cmd
{
	char	**exec_args;
	char	*infile;
	char	*outfile;
	bool	append;
	char	*limiter;
	int		connector;
	int		z_index;
}	t_cmd;

/*parsing*/
bool	parse(t_list **alst, const char *line);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
void	del_cmd(void *);

#endif
