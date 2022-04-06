/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:35 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/06 13:33:06 by vrogiste         ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	bool	append;
	char	*limiter;
	int		connector;
	int		z_index;
}	t_cmd;

/*parsing*/
t_list	*get_parsed_lst(const char *line);

/*new_cmd*/
void	init_cmd(t_cmd *cmd);
void	del_cmd(void *cmd);

//TEST
void	print_lst(t_list *lst);

#endif
