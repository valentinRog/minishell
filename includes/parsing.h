/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/04 12:08:12 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define SPACES " "
# define QUOTES "\"\'"

enum e_con
{
	con_NONE,
	con_PIPE,
	con_AND,
	con_OR
};

enum e_z
{
	z_NONE,
	z_INCR,
	z_DECR,
	z_RESET
};

typedef struct s_cmd
{
	t_list		*args;
	char		*infile;
	t_list		*outfiles;
	bool		append;
	char		*heredoc;
	enum e_con	con;
	int			z_index;
}	t_cmd;

/*parsing*/
t_list		*get_parsed_lst(char *line);

/*parse_arg*/
enum e_con	get_con(char *sep);
bool		parse_arg(t_cmd *cmd, char *arg, char *con);

/*new_cmd*/
void		init_cmd(t_cmd *cmd);
t_cmd		*new_cmd(t_cmd **dst);
void		del_cmd(void *args);

/*parenthesis*/
int			z_index(enum e_z z);
bool		parenthesis(t_cmd *cmd, char *arg, char *con);

#endif
