/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:57 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/06 17:08:47 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	execution_while(t_command *commands, int fd[2])
{
	int	i;
	int	flag;

	i = 0;
	while (commands[i].is_end)
	{
		if (i == 1)
		{
			i = until_last_command(commands, fd);
			if (i == -1)
				return (commands->is_end = 2, (void)0);
			if (commands[i + 1].is_end)
				return (end_of_pipeline(commands, fd, i));
		}
		flag = fork_command(&commands[i], i);
		if (flag == 1)
			return (end_of_pipeline(commands, fd, i));
		if (flag == 2)
			return (commands->is_end = 2, (void)0);
		i++;
	}
	end_of_pipeline(commands, fd, i);
}

void	execution_pipeline(t_command *commands)
{
	int	fd[2];
	int	flag;

	flag = g_status;
	set_position(commands);
	pipeline_start(commands, fd);
	if (g_status != flag)
		return ;
	return (execution_while(commands, fd));
}

void	execute_pipeline(t_pipeline pipeline, t_blocks *blocks)
{
	int		exit_value;

	if (pipeline.commands->arguments
		&& !ft_strncmp("exit", pipeline.commands->arguments[0], 5)
		&& !pipeline.commands[1].is_end)
	{
		exit_value = exit_ms(pipeline.commands);
		if (exit_value)
			exit_process(pipeline, blocks);
		return ;
	}
	(void)get_pipeline_singleton(&pipeline);
	execution_pipeline(pipeline.commands);
	if (pipeline.commands->is_end == 2)
		exit_process(pipeline, blocks);
}
