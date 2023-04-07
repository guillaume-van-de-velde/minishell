/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:11 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 22:19:48 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	arguments_conditions(char *line)
{
	return (!is_pipe(line) && !is_operator(line) && !is_parenthesis(line));
}

int	get_arguments(char **line, t_command *command, t_heredoc_fds **heredoc_fds)
{
	char	**args;
	int		status;

	status = 0;
	while (**line && arguments_conditions(*line) && !status)
	{
		if (!is_redirection(*line) && !status)
		{
			args = get_line_args(line, is_export_command(command));
			command->arguments = join_str_arr(command->arguments, args);
			if (!command->arguments)
				return (ENOMEM);
		}
		else
			status = get_redirections(line, command, heredoc_fds);
		skip_spaces(line);
	}
	return (status);
}

int	get_command(char **line, t_pipeline *pipeline,
	t_command *command, t_heredoc_fds **heredoc_fds)
{
	int	status;

	command->output_file = 1;
	command->is_end = 1;
	status = get_arguments(line, command, heredoc_fds);
	if (status == ENOMEM)
		return (ENOMEM);
	if (status)
		return (skip_command(line, pipeline, heredoc_fds), 0);
	if (str_arr_size(command->arguments) == 0)
	{
		free_str_arr(command->arguments);
		command->arguments = NULL;
	}
	if (command->arguments)
	{
		command->arguments = handle_widlcards(command->arguments);
		if (!command->arguments)
			return (ENOMEM);
		file_or_dir_check(command, command->arguments[0], EXEC);
	}
	*line += is_pipe(*line);
	return (0);
}

void	handle_parenthesis(char **line, t_pipeline *pipeline, char parenthesis)
{
	skip_spaces(line);
	if (**line != parenthesis)
		return ;
	skip_spaces(line);
	while (**line == parenthesis)
	{
		*line += 1;
		pipeline->parenthesis += (parenthesis == '(') * 2 - 1;
		skip_spaces(line);
	}
}

int	get_pipeline(char **line, t_pipeline *pipeline, t_heredoc_fds **heredoc_fds)
{
	int	i;
	int	size;

	pipeline->parenthesis = 0;
	handle_parenthesis(line, pipeline, '(');
	size = get_pipeline_commands_amount(*line);
	pipeline->commands = ft_calloc(size + 1, sizeof(t_command));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		if (get_command(line, pipeline, pipeline->commands + i, heredoc_fds)
			== ENOMEM)
			return (ENOMEM);
		handle_parenthesis(line, pipeline, ')');
		i++;
	}
	get_operator(line, pipeline);
	check_last_command_status(pipeline);
	return (0);
}
