/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_steps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:45 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:18:45 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	is_child(t_command command)
{
	if (!command.arguments || !command.arguments[0] || !command.arguments[0][0])
		return (1);
	if (!ft_strncmp(command.arguments[0], "cd", 3))
		return (0);
	if (!ft_strncmp(command.arguments[0], "export", 7))
		return (0);
	if (!ft_strncmp(command.arguments[0], "unset", 6))
		return (0);
	return (1);
}

void	pipeline_start(t_command *commands, int fd[2])
{
	if (commands[1].is_end)
		set_pipe(commands, fd);
	else
	{
		commands->position = 2;
		commands->close_pipe[0] = -1;
		commands->close_pipe[1] = -1;
	}
}

int	fork_command(t_command *command, int i)
{
	if (i != 0 || command[1].is_end || is_child(command[0]))
	{
		command->pid = fork();
		if (command->pid == -1)
			return (g_status = errno, perror("minishell: fork"), 1);
		if (command->pid == 0)
		{
			child_signals();
			execution_command(command);
			close_file(command->output_file);
			close_file(command->input_file);
			close_file(command->close_pipe[0]);
			close_file(command->close_pipe[1]);
			return (2);
		}
	}
	else
		execution_env(command);
	return (0);
}

int	until_last_command(t_command *commands, int fd[2])
{
	int	i;

	i = 1;
	if (close(fd[1]) == -1)
		(perror("minishell: close"), g_status = errno);
	if (commands[i].position == 0)
		i = multi_pipes(commands, &fd[0]);
	return (i);
}
