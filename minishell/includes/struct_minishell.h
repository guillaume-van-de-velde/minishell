/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:40:59 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/06 18:07:17 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MINISHELL_H
# define STRUCT_MINISHELL_H

# define SIGINT_HEREDOC -1

enum e_realloc_data_types {
	PIPELINES,
	COMMANDS,
	STR_ARR,
	INT_ARR
};

enum e_operators {
	NONE = 0,
	AND = 1,
	OR = 2,
};

enum e_redirections {
	SIMPLE_LEFT = 1,
	SIMPLE_RIGHT = 2,
	DOUBLE_LEFT = 3,
	DOUBLE_RIGHT = 4,
	PIPE = 5,
};

enum e_access_types {
	ACCESS_NONE,
	EXEC,
	WRITE,
	READ
};

typedef struct s_command
{
	char	**arguments;
	int		input_file;
	int		output_file;
	int		position;
	int		close_pipe[2];
	int		is_end;
	pid_t	pid;
	int		signal_stop;
	int		status;
}				t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			operator;
	int			parenthesis;
}				t_pipeline;

typedef struct t_heredoc_fds {
	int	fds[2];
	int	is_end;
}				t_heredoc_fds;

typedef struct s_blocks
{
	char			*line_ptr;
	t_heredoc_fds	*heredoc_ptr;
}				t_blocks;

typedef struct s_heredoc_data {
	char			**limits;
	t_heredoc_fds	*heredoc_fds;
}				t_heredoc_data;

typedef struct s_wildcard_info {
	int	directory_match;
	int	has_prefix;
}				t_wildcard_info;

#endif