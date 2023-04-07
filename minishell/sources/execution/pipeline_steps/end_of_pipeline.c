/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:18:42 by svan-de-          #+#    #+#             */
/*   Updated: 2023/04/05 19:33:24 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	call_to_waitpid(t_command *commands, int i)
{
	int	status_w;

	status_w = 0;
	if (waitpid(commands[i].pid, &status_w, 0) == -1)
		(perror("minishell: waitpid"), g_status = errno);
	if (!commands[i].status)
	{
		if (WIFEXITED(status_w))
			g_status = WEXITSTATUS(status_w);
		if (WIFSIGNALED(status_w))
		{
			g_status = 128 + WTERMSIG(status_w);
			commands[i].signal_stop = 1;
			if (WTERMSIG(status_w) == 2)
				write(1, "\n", 2);
			if (WTERMSIG(status_w) == 3)
				write(2, "Quit (core dumped)\n", 20);
		}
	}
	else
		g_status = commands[i].status;
}

void	end_of_pipeline(t_command *commands, int fd[2], int end)
{
	int	i;

	i = -1;
	signal_for_wait();
	if (commands[1].is_end && close(fd[0]) == -1)
		(perror("minishell: close"), g_status = errno);
	while (commands[++i].is_end && i < end)
	{
		if (i != 0 || commands[i + 1].is_end || is_child(commands[i]))
			call_to_waitpid(commands, i);
	}
}
