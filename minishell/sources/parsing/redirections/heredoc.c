/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:56 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:49:33 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_heredoc_fd(char **line, t_command *command,
	t_heredoc_fds **heredoc_fds)
{
	char		*heredoc_limit;

	if (command->input_file > 2)
		close(command->input_file);
	command->input_file = (**heredoc_fds).fds[0];
	(**heredoc_fds).fds[0] = 0;
	*heredoc_fds += 1;
	heredoc_limit = NULL;
	heredoc_limit = get_heredoc_limit(line, heredoc_limit);
	if (!heredoc_limit)
		return (ENOMEM);
	free(heredoc_limit);
	return (0);
}
