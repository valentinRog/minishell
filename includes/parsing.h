/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/13 15:15:48 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define SPACES " "
# define QUOTES "\"\'"

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
void	del_cmd(void *args);

//TEST
void	print_lst(t_list *lst);

#endif
