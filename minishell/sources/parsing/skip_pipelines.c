/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_pipelines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:30:21 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 22:20:34 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	check_last_command_status(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (pipeline->commands && pipeline->commands[i].is_end)
	{
		if (pipeline->commands[i].status)
		{
			free_str_arr(pipeline->commands[i].arguments);
			pipeline->commands[i].arguments = NULL;
		}
		if (!pipeline->commands[i + 1].is_end && pipeline->commands[i].status)
		{
			g_status = pipeline->commands[i].status;
			if (i == 0)
			{
				free_pipeline(*pipeline);
				pipeline->commands = NULL;
			}
		}
		i++;
	}
}

void	skip_command(char **line, t_pipeline *pipeline,
	t_heredoc_fds **heredoc_fds)
{
	while (**line && !is_pipe(*line) && !is_operator(*line))
	{
		if (is_quote(**line))
			check_quotes(line);
		else if (is_heredoc(*line))
		{
			close((**heredoc_fds).fds[0]);
			(**heredoc_fds).fds[0] = 0;
			*heredoc_fds += 1;
			skip_special_symbol(line);
		}
		if (is_parenthesis(*line))
			handle_parenthesis(line, pipeline, ')');
		else
			*line += 1;
	}
	*line += is_pipe(*line);
}

int	skip_pipeline(char **line, t_pipeline *pipeline,
	t_heredoc_fds **heredoc_fds)
{
	pipeline->parenthesis = 0;
	handle_parenthesis(line, pipeline, '(');
	while (**line && !is_operator(*line))
	{
		skip_command(line, pipeline, heredoc_fds);
	}
	get_operator(line, pipeline);
	return (0);
}

void	skip_pipeline_group(char **line, t_heredoc_fds *heredoc_fds)
{
	t_pipeline	curr;
	int			parenthesis;

	parenthesis = 0;
	while (**line)
	{
		if (skip_pipeline(line, &curr, &heredoc_fds))
			continue ;
		if (parenthesis == 0 && curr.parenthesis < 0)
			break ;
		parenthesis += curr.parenthesis;
		if (!parenthesis)
			break ;
	}
	skip_pipelines_to_not_execute(line, curr, heredoc_fds);
}

void	skip_pipelines_to_not_execute(char **line, t_pipeline last,
	t_heredoc_fds *heredoc_fds)
{
	if (!**line)
		return ;
	if (g_status == 130 || g_status == 131)
	{
		while (**line)
			*line += 1;
		return ;
	}
	if (last.operator == AND && g_status)
		skip_pipeline_group(line, heredoc_fds);
	else if (last.operator == OR && !g_status)
		skip_pipeline_group(line, heredoc_fds);
}
