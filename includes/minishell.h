/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:40:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/04/26 15:05:26 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include <time.h>

# include <sys/wait.h>

# include <errno.h>

# include <stdbool.h>
# include <inttypes.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "data_struct.h"
# include "utils.h"
# include "parsing.h"
# include "main.h"
# include "get_next_line.h"
# include "env.h"
# include "builtins.h"
# include "exec.h"

int	g_exit_code;

#endif
