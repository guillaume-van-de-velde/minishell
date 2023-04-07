/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:54 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 20:30:23 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	get_redirect_type(char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (DOUBLE_LEFT);
	else if (!ft_strncmp(*line, ">>", 2))
		return (DOUBLE_RIGHT);
	else if (**line == '<' && *(*line + 1) != '<')
		return (SIMPLE_LEFT);
	return (SIMPLE_RIGHT);
}

void	*get_red_function(int redirect_type)
{
	if (redirect_type == SIMPLE_RIGHT)
		return (handle_simple_right_redirection);
	else if (redirect_type == DOUBLE_RIGHT)
		return (handle_double_right_redirection);
	return (handle_simple_left_redirection);
}

int	handle_redirections(char **line, t_command *command,
	int red_function(t_command *, char *))
{
	char	*line_cpy;
	char	**file_names;
	int		status;
	char	**args;

	line_cpy = *line;
	args = get_line_args(line, is_export_command(command));
	file_names = handle_widlcards(args);
	if (!file_names)
		return (ENOMEM);
	if (str_arr_size(file_names) != 1)
	{
		command->status = 1;
		free_str_arr(file_names);
		print_error("ambiguous redirect: ", line_cpy);
		return (1);
	}
	status = red_function(command, file_names[0]);
	return (free_str_arr(file_names), status);
}

int	get_redirections(char **line, t_command *command,
	t_heredoc_fds **heredoc_fds)
{
	int		redirect_type;
	void	*redirection_function;
	int		status;

	status = 0;
	while (!status && is_redirection(*line))
	{
		redirect_type = get_redirect_type(line);
		skip_special_symbol(line);
		skip_spaces(line);
		if (redirect_type == DOUBLE_LEFT)
		{
			if (assign_heredoc_fd(line, command, heredoc_fds))
				return (1);
		}
		else
		{
			redirection_function = get_red_function(redirect_type);
			status = handle_redirections(line, command, redirection_function);
		}
		skip_spaces(line);
	}
	return (status);
}
