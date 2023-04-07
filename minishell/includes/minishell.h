/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:41:06 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 21:40:59 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NC		"\033[0m"
# define CYAN	"\033[1;36m"
# define GREEN	"\033[1;32m"
# define RED	"\033[1;31m"
# define BOLD	"\033[1m"
# define WHITE	"\033[0m"

# define PROMPT			"\001\033[1;32m\002▸ \
\001\033[1;32m\002minishell\001\033[0m\002 "
# define PROMPT_ERROR	"\001\033[1;31m\002▸ \
\001\033[1;32m\002minishell\001\033[0m\002 "
# define MEM "minishell: Cannot allocate memory\n"
# define LMIN "-9223372036854775808"
# define LMAX "9223372036854775807"

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "struct_minishell.h"
# include "parsing.h"
# include "execution.h"

int			hook_signals(void);
char		***environnement(char **new_env);
int			main(int argc, char **argv, char **env);

#endif