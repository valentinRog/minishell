/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/11 16:17:19 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define WHITESPACES " "
# define QUOTES "\"\'"
# define RESERVED "<>"

# define INFILE "<"
# define OUTFILE ">"
# define APPEND ">>"
# define HEREDOC "<<"

typedef struct s_cmd
{
	char	**exec_args;
	char	*infile;
	char	**outfiles;
	bool	append;
	char	**limiters;
	char	*connector;
	int		z_index;
}	t_cmd;

/*parsing*/
void	parse_into_lst(t_list **alst, char *line);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
void	del_cmd(void *cmd);

/*parse_cmd*/
void	parse_cmd(t_cmd *cmd, char *cmd_line, char *con);

/*redirection*/
void	redirection(t_cmd *cmd, char *arg);

/*check*/
bool	check(char *str);

/*format*/
void	format(char **astr);

//TEST
void	print_lst(t_list *lst);

#endif
