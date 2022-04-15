/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/15 14:46:31 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define SPACES " "
# define QUOTES "\"\'"

enum
{
	NONE,
	PIPE,
	AND,
	OR
};

enum
{
	GET,
	INCR,
	DECR,
	RESET
};

typedef struct s_cmd
{
	t_list	*args;
	char	*infile;
	t_list	*outfiles;
	bool	append;
	t_list	*limiters;
	int		con;
	int		z_index;
}	t_cmd;

/*parsing*/
t_list	*get_parsed_lst(char *line);

/*parse_arg*/
bool	parse_arg(t_cmd *cmd, char *arg, char *con);

/*connector*/
int		get_con(char *sep);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
t_cmd	*new_cmd(t_cmd **dst);
void	del_cmd(void *args);

//TEST
void	print_lst(t_list *lst);
bool	parenthesis(t_cmd *cmd, char *arg, char *con);

int		z_index(int op);
#endif
