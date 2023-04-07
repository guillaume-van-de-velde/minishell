/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:19:12 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:19:12 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	set_position(t_command *commands)
{
	int	i;

	i = 0;
	commands->position = -1;
	while (commands[++i].is_end)
			commands[i].position = 0;
	commands[i - 1].position = 1;
}

void	set_pipe_files(t_command *command, int fd[2], int i)
{
	if (i == 0)
	{
		if (command->output_file == 1)
		{
			command->output_file = fd[1];
			command->close_pipe[1] = -1;
		}
		else
			command->close_pipe[1] = fd[1];
		command[i].close_pipe[0] = fd[0];
	}
	else if (!command[i + 1].is_end)
	{
		if (command[i].input_file > 2)
			command[i].close_pipe[0] = fd[0];
		else
		{
			command[i].input_file = fd[0];
			command[i].close_pipe[0] = -1;
		}
	}
}

void	set_pipe(t_command *command, int fd[2])
{
	int	i;

	i = 0;
	if (pipe(fd) == -1)
		return (g_status = errno, perror("minishell: pipe function"));
	while (command[i].is_end)
	{
		set_pipe_files(command, fd, i);
		i++;
	}
}

void	set_files(t_command *command, int link[2], int fd)
{
	if (command->input_file == 0)
		command->input_file = fd;
	if (command->output_file == 1)
	{
		command->output_file = link[1];
		command->close_pipe[1] = -1;
	}
	else
		command->close_pipe[1] = link[1];
	command->close_pipe[0] = link[0];
}

int	multi_pipes(t_command *commands, int *fd)
{
	int	i;
	int	link[2];
	int	flag;

	i = 1;
	while (commands[i].position == 0)
	{
		if (pipe(link) == -1)
			(perror("minishell: close"), g_status = errno);
		set_files(&commands[i], link, *fd);
		flag = fork_command(&commands[i], i);
		if (flag == 1)
			return (close(link[1]), close(link[0]), i);
		if (flag == 2)
			return (-1);
		if (dup2(link[0], *fd) == -1 || close(link[1]) == -1
			|| close(link[0]) == -1)
			(perror("minishell: multi pipe"), g_status = errno);
		i++;
	}
	return (i);
}
