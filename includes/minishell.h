/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvernimm <bvernimm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:40:56 by vrogiste          #+#    #+#             */
/*   Updated: 2022/05/05 10:22:07 by bvernimm         ###   ########.fr       */
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

# include <dirent.h>

# include <signal.h>
# include <termios.h>

# include "data_struct.h"
# include "utils.h"
# include "parsing.h"
# include "main.h"
# include "get_next_line.h"
# include "env.h"
# include "builtin.h"
# include "exec.h"

#endif
