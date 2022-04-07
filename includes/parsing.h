/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/07 21:54:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

enum
{
	INCREMENT,
	DECREMENT,
	RESET,
	NONE
};

# define WHITESPACES " "
# define QUOTES "\"\'"
# define RESERVED "<>&|"

typedef struct s_cmd
{
	char	**exec_args;
	char	**infiles;
	char	**outfiles;
	char	**append_files;
	char	*limiter;
	char	*connector;
	int		z_index;
}	t_cmd;

/*parsing*/
void	parse_into_lst(t_list **alst, char *line);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
void	del_cmd(void *cmd);

/*parse_cmd*/
bool	parse_cmd(t_cmd *cmd, char *cmd_line, char *con);

/*redirection*/
bool	redirection(t_cmd *cmd, char *arg);

/*format*/
void	format(char **astr);

//TEST
void	print_lst(t_list *lst);

#endif
