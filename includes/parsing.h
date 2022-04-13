/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 20:01:09 by vrogiste         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**exec_args;
	char	*infile;
	char	**outfiles;
	bool	append;
	char	**limiters;
	int		con;
	int		z_index;
}	t_cmd;

/*parsing*/
t_list	*get_parsed_lst(char *line);

/*connector*/
int		get_con(char *sep);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
t_cmd	*new_cmd(void);
void	del_cmd(void *args);

//TEST
void	print_lst(t_list *lst);

#endif
